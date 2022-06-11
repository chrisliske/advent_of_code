import input


def paper(length, width, height):
    side1 = length * width
    side2 = width * height
    side3 = height * length
    surface_area = side1 * 2 + side2 * 2 + side3 * 2
    side_list = [side1, side2, side3]
    side_list.sort()
    return surface_area + side_list[0]


def ribbon(length, width, height):
    lwh = [length, width, height]
    lwh.sort()
    volume = length * width * height
    perimeter = lwh[0] + lwh[0] + lwh[1] + lwh[1]
    return volume + perimeter


boxList = []
number = ''
box = []
otherChars = 0
total = 0
totalRibbon = 0
boxNum = 0

#test = r'''10x1x1
#2x3x4
#'''

for i in input.test:
    # test can be replaced with instructions.instructions2
    if i.isnumeric():
        number = number + i
    elif i == 'x' or i == '\n':
        box.append(int(number))
        number = ''
    else:
        otherChars += 1
    if i == '\n':
        boxList.append(box)
        box = []

for i in boxList:
    boxNum += 1
    total += paper(i[0], i[1], i[2])
    totalRibbon += ribbon(i[0], i[1], i[2])

print('there are', otherChars, 'other characters.\nthe elves need', total, 'square feet of wrapping paper.\nthere are',
      boxNum, 'presents to be wrapped.\nthey also need', totalRibbon, 'feet of ribbon')

# Correct ribbon: 3737498 (for my list)
# Correct Wrap:   1586300 (for my list)