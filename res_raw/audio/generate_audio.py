# Genera los efectos y musicas del Flappy Bird por sintesis (estilo retro / chiptune)
import numpy as np
from scipy.io import wavfile
import os, sys

SR = 44100
OUT = sys.argv[1]
os.makedirs(OUT, exist_ok=True)
rng = np.random.default_rng(7)

def t_axis(dur):
    return np.arange(int(SR * dur)) / SR

def phase_from_freq(freq):
    return np.cumsum(freq) / SR

def square(freq, duty=0.5):
    ph = phase_from_freq(freq) % 1.0
    return np.where(ph < duty, 1.0, -1.0)

def triangle(freq):
    ph = phase_from_freq(freq) % 1.0
    return 4 * np.abs(ph - 0.5) - 1

def noise(n):
    return rng.uniform(-1, 1, n)

def env(n, attack=0.005, release=0.05, sustain_level=1.0):
    e = np.ones(n) * sustain_level
    a = min(int(SR * attack), n)
    r = min(int(SR * release), n - a)
    if a > 0: e[:a] = np.linspace(0, sustain_level, a)
    if r > 0: e[n - r:] = np.linspace(sustain_level, 0, r)
    return e

def exp_decay(n, speed):
    return np.exp(-np.arange(n) / SR * speed)

def lowpass(x, alpha):
    y = np.zeros_like(x); acc = 0.0
    for i, v in enumerate(x):
        acc += alpha * (v - acc); y[i] = acc
    return y

def save(name, x, peak=0.8):
    x = x / (np.max(np.abs(x)) + 1e-9) * peak
    wavfile.write(os.path.join(OUT, name), SR, (x * 32767).astype(np.int16))

def note(n):  # numero MIDI -> Hz
    return 440.0 * 2 ** ((n - 69) / 12)

# ---------------- EFECTOS ----------------
# Salto: barrido rapido hacia arriba
d = 0.14; n = int(SR * d)
f = np.linspace(380, 950, n)
save("jump.wav", square(f, 0.25) * exp_decay(n, 18) * env(n, 0.002, 0.02), 0.6)

# Choque: golpe grave + ruido
d = 0.35; n = int(SR * d)
thump = square(np.linspace(160, 50, n), 0.5) * exp_decay(n, 14)
crash = lowpass(noise(n), 0.25) * exp_decay(n, 10)
save("hit.wav", thump * 0.6 + crash * 0.9, 0.8)

# Caida por debajo de la pantalla: silbido que baja
d = 0.7; n = int(SR * d)
f = np.geomspace(1100, 140, n)
save("fall.wav", triangle(f) * env(n, 0.005, 0.15), 0.7)

# Game over: notas descendentes
parts = []
for midi, dur in [(67, 0.16), (64, 0.16), (60, 0.16), (55, 0.5)]:
    n = int(SR * dur)
    parts.append(square(np.full(n, note(midi)), 0.5) * env(n, 0.005, 0.08) * (0.9 if dur < 0.3 else exp_decay(n, 3)))
save("game_over.wav", np.concatenate(parts), 0.6)

# Clic de menu: blip corto
d = 0.06; n = int(SR * d)
save("click.wav", square(np.full(n, 1050.0), 0.25) * env(n, 0.001, 0.03), 0.5)

# Punto (pasar un cano): dos notas tipo moneda
p1 = int(SR * 0.07); p2 = int(SR * 0.22)
coin = np.concatenate([square(np.full(p1, note(83)), 0.5) * env(p1, 0.001, 0.005),
                       square(np.full(p2, note(88)), 0.5) * exp_decay(p2, 12)])
save("point.wav", coin, 0.5)

# Cuenta regresiva: beep corto
d = 0.12; n = int(SR * d)
save("countdown.wav", square(np.full(n, 660.0), 0.5) * env(n, 0.002, 0.04), 0.5)

# ---------------- MUSICAS (loops exactos) ----------------
def render_song(bpm, bars, tracks, total_gain=0.7):
    beat = 60.0 / bpm
    length = int(round(SR * beat * 4 * bars))
    mix = np.zeros(length)
    for start_beat, dur_beats, freq, wave, vol, decay in tracks:
        n = int(SR * dur_beats * beat)
        if freq is None:
            sig = lowpass(noise(n), 0.6)
        elif wave == "sq":
            sig = square(np.full(n, freq), 0.5)
        elif wave == "sq25":
            sig = square(np.full(n, freq), 0.25)
        elif wave == "kick":
            sig = np.sin(2 * np.pi * phase_from_freq(np.geomspace(150, 45, n)))
        else:
            sig = triangle(np.full(n, freq))
        sig = sig * env(n, 0.004, min(0.04, dur_beats * beat * 0.3)) * vol
        if decay: sig *= exp_decay(n, decay)
        s = int(round(SR * start_beat * beat))
        idx = (np.arange(n) + s) % length   # lo que se pasa del final vuelve al principio: loop sin cortes
        np.add.at(mix, idx, sig)
    return mix / (np.max(np.abs(mix)) + 1e-9) * total_gain

# Musica de menu: tranquila, Do mayor, C - Am - F - G
chords = [[60, 64, 67], [57, 60, 64], [53, 57, 60], [55, 59, 62]]
tracks = []
melody = [72, 71, 69, 67, 69, 72, 74, 76, 74, 72, 71, 69, 67, 69, 71, 72]
for bar in range(8):
    c = chords[bar % 4]
    tracks.append((bar * 4, 4, note(c[0] - 24), "tri", 0.55, 0))
    for i in range(8):  # arpegio en corcheas
        tracks.append((bar * 4 + i * 0.5, 0.5, note(c[i % 3] + 12), "tri", 0.25, 6))
    if bar >= 4:  # melodia en la segunda mitad
        for i in range(4):
            tracks.append((bar * 4 + i, 1, note(melody[((bar - 4) * 4 + i) % 16]), "sq25", 0.13, 2))
wav_menu = render_song(96, 8, tracks)
save("menu_music.wav", wav_menu, 0.7)

# Musica de gameplay: movida, La menor, Am - F - C - G
chords = [[57, 60, 64], [53, 57, 60], [48, 52, 55], [55, 59, 62]]
lead = [76, 74, 72, 74, 76, 79, 76, 74, 72, 71, 72, 74, 72, 71, 69, 71]
tracks = []
for bar in range(16):
    c = chords[bar % 4]
    for i in range(8):  # bajo en corcheas
        tracks.append((bar * 4 + i * 0.5, 0.5, note(c[0] - 12 + (12 if i % 2 else 0)), "tri", 0.6, 0))
    for b in range(4):  # bombo y hi-hat
        tracks.append((bar * 4 + b, 0.5, 1.0, "kick", 0.9, 9))
        tracks.append((bar * 4 + b + 0.5, 0.25, None, "", 0.18, 30))
    if bar >= 4:
        for i in range(8):  # melodia
            if bar >= 12 and i % 2: continue
            tracks.append((bar * 4 + i * 0.5, 0.5, note(lead[(bar * 8 + i) % 16]), "sq", 0.13, 3))
wav_game = render_song(140, 16, tracks)
save("game_music.wav", wav_game, 0.7)
print("ok")
