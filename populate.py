import numpy as np


TOT_PESSOAS = 1000000
TOT_CURSOS = 200
TOT_ELEMENTOS = 100000000

lines = np.empty((TOT_ELEMENTOS, 4))
pessoas = np.zeros((1, TOT_PESSOAS))

for x in range(TOT_PESSOAS):
    print 'Step 1-' + str(x)
    pes = np.array(1)
    for i in range(7):
        pes = np.array([pes, int(np.random.uniform((9,)))])
    pessoas[x] = pes
pessoas = np.unique(pessoas)

TOT_PESSOAS = pessoas.shape[0] * pessoas.shape[1]

for x in range(TOT_ELEMENTOS):
    print 'Step 2-' + str(x)
    lines[x][0] = int(np.random.uniform((9,)) + 732313)
    lines[x][1] = pessoas[int(np.random.uniform((TOT_PESSOAS,)))]
    lines[x][2] = int(np.random.uniform((TOT_CURSOS,)))
    lines[x][3] = int(np.random.uniform((20,)))

lines = lines.ravel().sort()
