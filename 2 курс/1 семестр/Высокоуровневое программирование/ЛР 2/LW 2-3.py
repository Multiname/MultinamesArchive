print(
    '\n'.join(
        '\n'.join(
            '\n'.join(
                '{} {} {} {}'.format(A, B, C, int(((A == B) == C) or not A))
                for C in range(2))
            for B in range(2))
        for A in range(2)))
