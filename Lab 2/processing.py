import matplotlib.pyplot as plt
import numpy as np

part = 2
if part == 1:
    indexes = ['N=1', 'N=2', 'N=3', 'N=4']

    times_wo_optim_integral = np.array([1.952, 1.906, 1.845, 1.9])
    times_optim_o2_integral = np.array([0.459, 0.448, 0.437, 0.44])
    times_wo_optim_array = np.array([3.903, 0.706, 0.66, 0.698])
    times_optim_o2_array = np.array([0.16, 0.112, 0.136, 0.136])

    plt.scatter(indexes, times_wo_optim_integral, label='Integral, without optimization', s=60, c='b')
    plt.scatter(indexes, times_optim_o2_integral, label='Integral, -O2', s=60, c='r')
    plt.scatter(indexes, times_wo_optim_array, label='Array, without optimization', s=60, c='g')
    plt.scatter(indexes, times_optim_o2_array, label='Array, -O2', s=60, c='#9467bd')
    plt.ylabel("t, sec")
    plt.legend()
    plt.grid(True)
    plt.show()

elif part == 2:
    threads = np.arange(1, 5)

    times_spmd = np.array([2.199, 1.467, 0.902, 0.747])
    times_array = np.array([2.064, 1.824, 1.659, 1.664])
    times_critical = np.array([2.416, 1.253, 0.907, 0.763])
    times_atomic = np.array([1.962, 1.107, 0.888, 0.7])
    times_lock = np.array([2.08, 1.186, 0.864, 0.725])
    times_do = np.array([2.074, 1.113, 0.935, 0.726])

    plt.scatter(threads, times_spmd, label='spmd', s=60, c='b')
    plt.scatter(threads, times_array, label='array', s=60, c='r')
    plt.scatter(threads, times_critical, label='critical', s=60, c='g')
    plt.scatter(threads, times_atomic, label='atomic', s=60, c='#9467bd')
    plt.scatter(threads, times_lock, label='lock', s=60, c='#8c564b')
    plt.scatter(threads, times_do, label='do', s=60, c='#17becf')
    plt.ylabel("t, sec", fontsize=12)
    plt.legend()
    plt.grid(True)
    plt.show()

    s_spmd = [times_spmd[0] / time for time in times_spmd]
    s_array = [times_array[0] / time for time in times_array]
    s_critical = [times_critical[0] / time for time in times_critical]
    s_atomic = [times_atomic[0] / time for time in times_atomic]
    s_lock = [times_lock[0] / time for time in times_lock]
    s_do = [times_do[0] / time for time in times_do]

    plt.scatter(threads, s_spmd, label='spmd', s=60, c='b')
    plt.scatter(threads, s_array, label='array', s=60, c='r')
    plt.scatter(threads, s_critical, label='critical', s=60, c='g')
    plt.scatter(threads, s_atomic, label='atomic', s=60, c='#9467bd')
    plt.scatter(threads, s_lock, label='lock', s=60, c='#8c564b')
    plt.scatter(threads, s_do, label='do', s=60, c='#17becf')
    plt.ylabel("Sp", fontsize=12)
    plt.legend()
    plt.grid(True)
    plt.show()

    e_spmd = [s_spmd[i] / threads[i] for i in range(len(s_spmd))]
    e_array = [s_array[i] / threads[i] for i in range(len(s_array))]
    e_critical = [s_critical[i] / threads[i] for i in range(len(s_critical))]
    e_atomic = [s_atomic[i] / threads[i] for i in range(len(s_atomic))]
    e_lock = [s_lock[i] / threads[i] for i in range(len(s_lock))]
    e_do = [s_do[i] / threads[i] for i in range(len(s_do))]

    plt.scatter(threads, e_spmd, label='spmd', s=60, c='b')
    plt.scatter(threads, e_array, label='array', s=60, c='r')
    plt.scatter(threads, e_critical, label='critical', s=60, c='g')
    plt.scatter(threads, e_atomic, label='atomic', s=60, c='#9467bd')
    plt.scatter(threads, e_lock, label='lock', s=60, c='#8c564b')
    plt.scatter(threads, e_do, label='do', s=60, c='#17becf')
    plt.ylabel("Ep", fontsize=12)
    plt.legend()
    plt.grid(True)
    plt.show()


elif part == 3:
    indexes = ['static,1', 'static,10', 'static,100', 'static,1000',
               'static,10000', 'static,100000', 'static,1000000',
               'static,10000000', 'static,100000000', 'dynamic', 'guided']

    times = np.array([0.72, 0.715, 0.736, 0.731, 0.696, 0.747, 0.714, 0.822, 1.936, 2.589, 0.686])

    index = np.arange(len(indexes))
    bw = 0.9
    plt.bar(index, times, bw, color='b')
    plt.xticks(index, indexes, rotation=30, fontsize=10)
    plt.ylabel("t, sec", fontsize=12)
    plt.xlabel("schedule", fontsize=12)
    plt.yscale('log')
    plt.grid(axis="y", which='both')
    plt.show()
