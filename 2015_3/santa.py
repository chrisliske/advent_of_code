def move(pos, dir):
        if dir == '>':
            pos = (pos[0] + 1, pos[1])
        elif dir == '<':
            pos = (pos[0] - 1, pos[1])
        elif dir == '^':
            pos = (pos[0], pos[1] + 1)
        elif dir == 'v':
            pos = (pos[0], pos[1] - 1)
        else:
            print('invalid input: {}'.format(dir))
        return pos


def main():
    with open('input.txt', 'r') as input:
        directions = input.readline()
    
    ## Day 3 Part One
    position = (0, 0)
    visited = set([position])  # unique locations visited
    for direction in directions:
        position = move(position, direction)
        visited.add(position)
    print('Part One: {} unique houses visited'.format(len(visited)))
    
    ## Day 3 Part Two
    startPosition = (0, 0)
    santaPosition = startPosition
    roboSantaPosition = startPosition
    visited = set([startPosition])  # unique locations visited
    for i, direction in enumerate(directions, start=1):
        if i % 2 != 0:  # santa takes odd numbered directions
            santaPosition = move(santaPosition, direction)
            visited.add(santaPosition)
        else:
            roboSantaPosition = move(roboSantaPosition, direction)
            visited.add(roboSantaPosition)
    print('Part Two: {} unique houses visited'.format(len(visited)))


if __name__ == '__main__':
    main()