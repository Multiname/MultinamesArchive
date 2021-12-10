from PIL import Image, ImageFilter

Image.open('cat.jpg').filter(ImageFilter.BLUR).crop(
    (100, 100, 800, 1000)).save('cat_1.jpg', 'JPEG')
