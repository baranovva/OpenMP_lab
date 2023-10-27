import matplotlib.pyplot as plt
import numpy as np

part = 4
if part == 1:
    from itertools import permutations

    indexes = permutations('ijk', 3)

    times_wo_optim = np.array([1.578, 1.781, 1.635, 4.629, 11.793, 13.763])
    times_optim_o1 = np.array([0.987, 0.94, 1.088, 2.458, 7.062, 6.434])
    times_optim_o2 = np.array([0.67, 0.8, 0.779, 2.346, 4.643, 5.665])

    index = np.arange(len(indexes))
    bw = 0.3
    plt.axis([-0.5, 6, 0, 14])
    plt.bar(index, times_wo_optim, bw, color='b', label='Without optimization')
    plt.bar(index + bw, times_optim_o1, bw, color='g', label='-O1')
    plt.bar(index + 2 * bw, times_optim_o2, bw, color='r', label='-O2')
    plt.xticks(index + 1 * bw, indexes)
    plt.ylabel("t, sec")
    plt.legend()
    plt.grid(axis="y")
    plt.show()

elif part == 2:
    indexes = ['static,1', 'static,2', 'static,5', 'static,10', 'static,25',
               'static,50', 'static,100', 'dynamic', 'guided']

    times = np.array([0.642, 0.715, 0.651, 0.885, 0.664, 1.112, 1.918, 0.608, 0.753])
    index = np.arange(len(indexes))

    bw = 0.6
    plt.axis([-0.5, len(indexes) - 0.5, 0, 2])
    plt.bar(index, times, bw, color='b')
    plt.xticks(index, indexes, fontsize=18)
    plt.ylabel("t, sec", fontsize=18)
    plt.grid(axis="y")
    plt.show()

elif part == 3:
    indexes = ['N = 1', 'N = 2', 'N = 3']

    times_wo_optim = np.array([1.918, 0.011, 0.015])
    times_optim_o2 = np.array([0.422, 0.008, 0.006])

    index = np.arange(len(indexes))
    bw = 0.4
    plt.bar(index, times_wo_optim, bw, color='b', label='Without optimization')
    plt.bar(index + 1 * bw, times_optim_o2, bw, color='r', label='-O2')
    plt.xticks(index + bw / 2, indexes)
    plt.ylabel("t, sec")
    plt.legend()
    plt.yscale('log')
    plt.grid(axis="y")
    plt.show()

    statics_val = ['static,1', 'static,2', 'static,5', 'static,10', 'static,25', 'static,50', 'static,100']

    times_wo_optim_static_N1 = np.array([0.642, 0.715, 0.651, 0.885, 0.664, 1.112, 1.918])
    times_optim_o2_static_N1 = np.array([0.486, 0.439, 0.452, 0.482, 0.45, 0.554, 0.894])
    times_wo_optim_static_N2 = np.array([0.016, 0.016, 0, 0.016, 0.015, 0.015, 0.006])
    times_optim_o2_static_N2 = np.array([0, 0.007, 0.016, 0, 0.015, 0, 0.016])
    times_wo_optim_static_N3 = np.array([0, 0.008, 0.007, 0, 0, 0.007, 0.015])
    times_optim_o2_static_N3 = np.array([0, 0, 0, 0, 0, 0, 0])

    plt.scatter(statics_val, times_wo_optim_static_N1, label='N = 1, without optimization', s=60, c='b')
    plt.scatter(statics_val, times_optim_o2_static_N1, label='N = 1, -O2', s=60, c='r')
    plt.scatter(statics_val, times_wo_optim_static_N2, label='N = 2, without optimization', s=60, c='g')
    plt.scatter(statics_val, times_optim_o2_static_N2, label='N = 2, -O2', s=60, c='#9467bd')
    plt.scatter(statics_val, times_wo_optim_static_N3, label='N = 3, without optimization', s=60, c='#8c564b')
    plt.scatter(statics_val, times_optim_o2_static_N3, label='N = 3, -O2', s=60, c='#17becf')
    plt.yscale('log')
    plt.ylabel("t, sec")
    plt.legend()
    plt.grid(True)
    plt.show()


elif part == 4:

    def plot(y_data_for: object, y_data_section: object, y_label: str) -> None:
        plt.scatter(threads, y_data_for, label="for program", s=60, c='b')
        plt.scatter(threads, y_data_section, label="section program", s=60, c='r')
        plt.ylabel(y_label)
        plt.xlabel("Number of threads")
        plt.legend()
        plt.grid(True)
        plt.show()


    threads = np.arange(1, 9)

    times_for = np.array([0.661, 0.531, 0.421, 0.404, 0.386, 0.39, 0.399, 0.415])
    times_sections = np.array([1.451, 1.01, 0.496, 0.527, 0.51, 0.507, 0.507, 0.51])

    plot(times_for, times_sections, "t, sec")

    s_for = [times_for[0] / time for time in times_for]
    s_sections = [times_sections[0] / time for time in times_sections]

    plot(s_for, s_sections, "Sp")

    e_for = [s_for[i] / threads[i] for i in range(len(s_for))]
    e_sections = [s_sections[i] / threads[i] for i in range(len(s_sections))]

    plot(e_for, e_sections, "Ep")
