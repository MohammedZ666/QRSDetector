from scipy.signal import butter, lfilter
import numpy as np
def bandpass_filter(data, lowcut, highcut, signal_freq, filter_order):
        """
        Method responsible for creating and applying Butterworth filter.
        :param deque data: raw data
        :param float lowcut: filter lowcut frequency value
        :param float highcut: filter highcut frequency value
        :param int signal_freq: signal frequency in samples per second (Hz)
        :param int filter_order: filter order
        :return array: filtered data
        """
        """Constructs signal filter and uses it to given data set."""
        nyquist_freq = 0.5 * signal_freq
        low = lowcut / nyquist_freq
        high = highcut / nyquist_freq
        b, a = butter(filter_order, [low, high], btype="band")
        y = lfilter(b, a, data)
        return y
def load_ecg_data():
    """
    Method loading ECG data set from a file.
    """
    return np.loadtxt("ecg_data/ecg_data_1.csv", skiprows=1, delimiter=',')
data = load_ecg_data()[:,1]
data_filtered = bandpass_filter(data, 5, 15, 250, 1)
data_filtered_cpp = np.loadtxt("filtered.txt")
trunc = np.vectorize(lambda x : float('%.3f'%(x)))

diffed = trunc(np.loadtxt("diff.txt"))
print(sum(diffed - trunc(np.ediff1d(data_filtered))))
