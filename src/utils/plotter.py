from scipy.io import wavfile
import matplotlib.pyplot as plt
import sys

try:
    if sys.argv[1]:
        # Input name in cli
        file = sys.argv[1]

    rate, data = wavfile.read(file)

    data = data / 32767

    plt.plot(data)

    plt.axis([0, len(data), -1.2, 1.2])
    plt.show()

except:
    print("Error: Invalid input")
    print("""
Correct use:
python3 plotter.py <pathToFile>""")
