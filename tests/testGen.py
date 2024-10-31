from random import randint

path = "/home/mafioznic/Документы/C-Vladimirov/matrix/tests/"

for test in range(1, 11):
    n = randint(2, 10)

    # n = 3
    arr = [[0] * n for _ in range(n)]  # Правильная инициализация массива

    ans = 1
    for i in range(n):
        arr[i][i] = randint(1, 5)  # Изменил на randint(1, 5) для избежания нуля на диагонали
        ans *= arr[i][i]

    for j in range(n):
        for i in range(n):
            if (i != j):
                coeff = randint(0, 5)
                for k in range(n):
                    arr[j][k] += arr[i][k] * coeff

    st = ""
    st += str(n) + '\n'
    for i in range(n):
        for j in range(n):
            st += str(arr[i][j]) + ' '
        st += '\n'

    with open(path + "test" + str(test) + ".dat", "w") as f:  # Используйте with для открытия файлов
        f.write(st)

    st = str(ans)
    with open(path + "test" + str(test) + ".ans", "w") as f:
        f.write(st)
