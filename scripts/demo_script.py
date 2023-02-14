def sine_wave_demo():
    """
    Simulate a sinusoidal signal with given sampling rate
    """
    import numpy as np
    import matplotlib.pyplot as plt  # library for plotting
    from signalgen import sine_wave  # import the function
    f = 10  # frequency = 10 Hz
    over_samp_rate = 30  # oversammpling rate
    phase = 1 / 3 * np.pi  # phase shift in radians
    n_cyl = 5  # desired number of cycles of the sine wave
    (t, g) = sine_wave(f, over_samp_rate, phase, n_cyl)  # function call
    plt.plot(t, g)  # plot using pyplot library from matplotlib package
    plt.title('Sine wave f=' + str(f) + 'Hz')  # plot title
    plt.xlabel('Time (s)')  # x-axis label
    plt.ylabel('Amplitude')  # y-axis label
    plt.show()  # display the figure


def square_wave_demo():
    import numpy as np
    import matplotlib.pyplot as plt  # library for plotting
    from signalgen import square_wave  # import the function
    f = 10  # frequency = 10 Hz
    over_samp_rate = 30  # oversammpling rate
    phase = 1 / 3 * np.pi  # phase shift in radians
    n_cyl = 5  # desired number of cycles of the sine wave
    (t, g) = square_wave(f, over_samp_rate, phase, n_cyl)  # function call
    plt.plot(t, g)  # plot using pyplot library from matplotlib package
    plt.title('Squire wave f=' + str(f) + 'Hz')  # plot title
    plt.xlabel('Time (s)')  # x-axis label
    plt.ylabel('Amplitude')  # y-axis label
    plt.show()  # display the figure


def chirp_demo():
    import numpy as np
    import matplotlib.pyplot as plt
    from scipy.signal import chirp
    fs = 500
    t = np.arange(start=0, stop=1, step=1 / fs)
    g = chirp(t, f0=1, t1=0.1, f1=20, phi=0, method="linear")
    plt.plot(t, g)
    plt.show()


def show_my_dft():
    import numpy as np
    import matplotlib.pyplot as plt  # library for plotting
    from signalgen import sine_wave  # import the function
    from my_dft_imp import my_dft_imp
    (t, g) = sine_wave(10, 30, 0, 10)
    (i, xre) = my_dft_imp(g)
    plt.plot(i, xre)
    plt.show()


def show_their_dft():
    from scipy.fftpack import fft, ifft
    import numpy as np
    import matplotlib.pyplot as plt
    from signalgen import cosine_wave
    np.set_printoptions(formatter={"float_kind": lambda x: "%g" % x})

    fc = 10  # frequency of the carrier
    over_sampling_rate = 32
    fs = fc * over_sampling_rate
    (t, x) = cosine_wave(fc, over_sampling_rate, 0, 20)  # 2 seconds
    fig, (ax1, ax2, ax3) = plt.subplots(nrows=3, ncols=1)
    ax1.plot(t, x)  # plot the signal
    ax1.set_title('$x[n]= cos(2 \pi 10 t)$')
    ax1.set_xlabel('$t=nT_s$')
    ax1.set_ylabel('$x[n]$')

    N = 256
    X = fft(x, N)

    df = fs / N
    sampleIndex = np.arange(start=0, stop=N)
    f = sampleIndex * df
    ax2.stem(sampleIndex, abs(X), use_line_collection=True)  # sample values on x-axis
    ax2.set_title('X[k]')
    ax2.set_xlabel('k')
    ax2.set_ylabel('|X(k)|')
    ax3.stem(f, abs(X), use_line_collection=True)  # x-axis represent frequencies
    ax3.set_title('X[f]')
    ax3.set_xlabel('frequencies (f)')
    ax3.set_ylabel('|X(f)|')

    plt.tight_layout()
    plt.show()


def phase_and_amplitude():
    from scipy.fftpack import fft, ifft, fftshift, ifftshift
    import numpy as np
    import matplotlib.pyplot as plt
    A = 0.5  # amplitude of the cosine wave
    fc = 10  # frequency of the cosine wave in Hz
    phase = 30  # desired phase shift of the cosine in degrees
    fs = 32 * fc  # sampling frequency with oversampling factor 32
    t = np.arange(start=0, stop=2, step=1 / fs)  # 2 seconds duration
    phi = phase * np.pi / 180  # convert phase shift in degrees in radians
    x = A * np.cos(2 * np.pi * fc * t + phi)  # time domain signal with phase shift
    fig, (ax1, ax2, ax3, ax4) = plt.subplots(nrows=4, ncols=1)
    ax1.plot(t, x)  # plot time domain representation
    ax1.set_title(r'$x(t) = 0.5 cos (2 \pi 10 t + \pi/6)$')
    ax1.set_xlabel('time (t seconds)');
    ax1.set_ylabel('x(t)')
    plt.tight_layout()
    plt.show()


phase_and_amplitude()
