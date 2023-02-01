import numpy as np
from numpy import ndarray


def sine_wave(f: float, over_sample_rate: float, phase: float, n_cyl: int) -> tuple[ndarray, ndarray]:
    fs = over_sample_rate * f
    t = np.arange(start=0, stop=n_cyl*1/f - 1/fs, step=1/fs)
    g = np.sin(2*np.pi * f * t + phase)
    return t, g

