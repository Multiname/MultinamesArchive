import math

class Software():
    name = ''
    usage = []
    size = []
    cost = 0

    def __init__(self, name, usage, size, cost):
        self.name = name
        self.usage = usage
        self.size = size
        self.cost = cost

MOYSKLAD = Software(
    'MOYSKLAD',
    ['warehouse'],
    ['small', 'medium'],
    5400
    )

EKAM = Software(
    'EKAM',
    ['warehouse'],
    ['small', 'medium'],
    9600
    )

U4ET_small = Software(
    'U4ET (малый бизнес)',
    ['warehouse'],
    ['small'],
    12000
    )

U4ET_medium = Software(
    'U4ET (средний бизнес)',
    ['warehouse'],
    ['medium'],
    60000
    )

RBS_CRM = Software(
    'RBS CRM',
    ['warehouse'],
    ['small', 'medium'],
    17880
    )

MOE_DELO = Software(
    'Мое дело',
    ['warehouse', 'accounting'],
    ['small', 'medium'],
    18000
    )

INFO_PREDPRIYATIE = Software(
    'Инфо-Предприятие',
    ['accounting'],
    ['small'],
    0
    )

_1C = Software(
    '1C:БизнесСтарт',
    ['accounting'],
    ['small'],
    3000
    )

SBIS = Software(
    'СБИС Бухгалтерия и учет',
    ['accounting'],
    ['small', 'medium'],
    4900
    )

softwares = [MOYSKLAD, EKAM, U4ET_small, U4ET_medium, RBS_CRM,
             MOE_DELO, INFO_PREDPRIYATIE, _1C, SBIS]
options = [MOYSKLAD, EKAM, U4ET_small, U4ET_medium, RBS_CRM,
             MOE_DELO, INFO_PREDPRIYATIE, _1C, SBIS]

print('Выберите назначение ПО')
print('1. Склад')
print('2. Бухгалтерия')
selection = int(input('>>> '))
print()

usage = ['warehouse', 'accounting']

for i in range(len(options) - 1, -1, -1):
    if not (usage[selection - 1] in options[i].usage):
        options.pop(i)

print('Укажите размер бизнеса')
print('1. Малый')
print('2. Средний')
selection = int(input('>>> '))
print()

size = ['small', 'medium']

for i in range(len(options) - 1, -1, -1):
    if not (size[selection - 1] in options[i].size):
        options.pop(i)

print('Укажите желаемую стоимость годовой оплаты')
cost = int(input('>>> '))
print()

minDelta = math.inf
mostSuitableIndex = 0
for i in range(len(options) - 1, -1, -1):
    delta = abs(options[i].cost - cost)
    if delta < minDelta:
        minDelta = delta
        mostSuitableIndex = i

print('Варианты и итоговое решение')
print('{:28}'.format('Название'), end='|')
print(' Склад ', end='|')
print(' Бухгалтерия ', end='|')
print(' Малый б. ', end='|')
print(' Средний б. ', end='|')
print(' Цена в год')
for sw in softwares:
    print('{:28}'.format('>>> ' + sw.name if sw.name == options[mostSuitableIndex].name else sw.name), end='|')
    print('   +   ' if 'warehouse' in sw.usage else '   -   ', end='|')
    print('      +      ' if 'accounting' in sw.usage else '      -      ', end='|')
    print('    +     ' if 'small' in sw.size else '    -     ', end='|')
    print('     +      ' if 'medium' in sw.size else '     -      ', end='|')
    print('', sw.cost)

