def get_frequency(text: str):
    symbols = {}
    for s in text:
        if not s.isalpha():
            continue

        s = s.lower()
        if s in symbols:
            symbols[s] += 1
        else:
            symbols[s] = 1

    symbols = dict(sorted(symbols.items(), key=lambda item: item[1], reverse=True))
    length = len(text)
    for s in symbols:
        symbols[s] /= length
        print(f'{s}: {symbols[s]*100:.4f}%')

    return symbols

source_file = open('source.txt', 'r')
source_text = source_file.read()
source_symbols = get_frequency(source_text)
source_keys = list(source_symbols.keys())

print()

encrypted_file = open('encrypted.txt', 'r')
encrypted_text = encrypted_file.read()
encrypted_symbols = get_frequency(encrypted_text)
encrypted_keys = list(encrypted_symbols.keys())

decrypted_text = ''
for s in encrypted_text:
    if not s.isalpha():
        decrypted_text += s
        continue

    s = s.lower()
    index = encrypted_keys.index(s)
    if index >= len(source_keys):
        decrypted_text += '?'
        continue
    decrypted_text += source_keys[index]

print(decrypted_text)

fixed_text = decrypted_text
def swap_letters(a, b):
    global fixed_text

    fixed_text = fixed_text.replace(a, '#')
    fixed_text = fixed_text.replace(b, a)
    fixed_text = fixed_text.replace('#', b)

swap_letters('л', 'к')
swap_letters('а', 'н')
swap_letters('т', 'с')
swap_letters('т', 'и')
swap_letters('д', 'у')
swap_letters('т', 'л')
swap_letters('к', 'в')
swap_letters('д', 'н')
swap_letters('ч', 'ь')
swap_letters('х', 'ш')
swap_letters('л', 'р')
swap_letters('б', 'ы')
swap_letters('л', 'к')
swap_letters('л', 'н')
swap_letters('з', 'п')
swap_letters('л', 'з')
swap_letters('т', 'л')
swap_letters('у', 'г')
swap_letters('ч', 'б')
swap_letters('д', 'т')
swap_letters('ж', 'ч')
swap_letters('ж', 'я')
swap_letters('ж', 'д')
swap_letters('у', 'ж')
swap_letters('ц', 'щ')
swap_letters('ю', 'х')
swap_letters('?', 'э')
fixed_text = fixed_text.replace('?', 'ъ')

print(fixed_text)

fixed_symbols = dict.fromkeys(encrypted_keys)

for i in range(len(fixed_text)):
    symbol = encrypted_text[i].lower()
    if not symbol.isalpha():
        continue
    
    fixed_symbol = fixed_text[i]
    fixed_symbols[symbol] = fixed_symbol

for s in fixed_symbols:
    print(f'{s} = {fixed_symbols[s]}')