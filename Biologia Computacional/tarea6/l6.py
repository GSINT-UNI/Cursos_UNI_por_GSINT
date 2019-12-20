def viterbi(obs, states, start_p, trans_p, emit_p):

    V = [{}]

    for st in states:

        V[0][st] = {"prob": start_p[st] * emit_p[st][obs[0]], "prev": None}

    # corre Viterbi cuando t > 0

    for t in range(1, len(obs)):

        V.append({})

        for st in states:

            max_tr_prob = V[t-1][states[0]]["prob"]*trans_p[states[0]][st]

            prev_st_selected = states[0]

            for prev_st in states[1:]:

                tr_prob = V[t-1][prev_st]["prob"]*trans_p[prev_st][st]

                if tr_prob > max_tr_prob:

                    max_tr_prob = tr_prob

                    prev_st_selected = prev_st

                    

            max_prob = max_tr_prob * emit_p[st][obs[t]]

            V[t][st] = {"prob": max_prob, "prev": prev_st_selected}

                    

    for line in dptable(V):

        print( line )

    opt = []

    # busca la mayor probabilidad

    max_prob = max(value["prob"] for value in V[-1].values())

    previous = None

    # regresa el estado mas probable y su camino

    for st, data in V[-1].items():

        if data["prob"] == max_prob:

            opt.append(st)

            previous = st

            break

    # sigue por ese camino hasta llegar a la primera observación

    for t in range(len(V) - 2, -1, -1):

        opt.insert(0, V[t + 1][previous]["prev"])

        previous = V[t + 1][previous]["prev"]


    print ('los saltos de estado son ' + ' '.join(opt) + ' con la mayor probabilidad de %s' % max_prob)


def dptable(V):

    # imprime la tabla de pasos con el diccionario

    yield " ".join(("%12d" % i) for i in range(len(V)))

    for state in V[0]:

        yield "%.7s: " % state + " ".join("%.7s" % ("%f" % v[state]["prob"]) for v in V)



obs = ('T', 'C', 'A', 'G')
states = ('island', 'genome')
start_p = {'island': 0.1, 'genome': 0.9}
trans_p = {
   'island' : {'island': 0.8, 'genome': 0.2},
   'genome' : {'island': 0.9, 'genome': 0.1}
   }
emit_p = {
   'island' : {'T': 0.4, 'C': 0.4, 'A': 0.1, 'G': 0.1},
   'genome' : {'T': 0.1, 'C': 0.1, 'A': 0.4, 'G': 0.4}
   }

viterbi(obs, states, start_p, trans_p, emit_p)

