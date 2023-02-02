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


chirp_demo()
