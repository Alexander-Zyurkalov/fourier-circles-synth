import numpy as np
from numpy import ndarray
from scipy import signal


def sine_wave(f: float, over_sample_rate: float, phase: float, n_cyl: int) -> tuple[ndarray, ndarray]:
    fs = over_sample_rate * f
    t = np.arange(start=0, stop=n_cyl * 1 / f, step=1 / fs)
    g = np.sin(2 * np.pi * f * t + phase)
    return t, g


def cosine_wave(f: float, over_sample_rate: float, phase: float, n_cyl: int) -> tuple[ndarray, ndarray]:
    fs = over_sample_rate * f
    t = np.arange(start=0, stop=n_cyl * 1 / f, step=1 / fs)
    g = np.cos(2 * np.pi * f * t + phase)
    return t, g


def square_wave(f: float, over_sample_rate, rate: float, n_cyl: int) -> tuple[ndarray, ndarray]:
    fs = over_sample_rate * f
    t = np.arange(0, n_cyl * 1 / f, 1 / fs)
    g = signal.square(2 * np.pi * f * t, duty=0.5)
    return t, g
