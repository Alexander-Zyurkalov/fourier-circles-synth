import numpy
from numpy.core.records import ndarray
import numpy as np


def my_dft_imp(xns: ndarray[float]) -> tuple[ndarray, ndarray]:
    N = int(xns.size)
    Xre = np.empty(int(N / 2), dtype=numpy.float32)

    for k in range(0, int(N / 2)):
        Xre[int(k)] = \
            2 / N * \
            np.sum(
                np.full(N,
                        fill_value=[
                            xns[int(n)] * np.cos(k * n * np.pi * 2 / N) for n in range(0, N)
                        ])
            )

    index = np.arange(0, int(N / 2), 1)
    return index, Xre
