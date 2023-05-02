def knight_moves(a, b):
    moves = [(-2, -1), (-1, -2), (1, -2), (2, -1),
             (2, 1), (1, 2), (-1, 2), (-2, 1)]

    ax, ay = ord(a[0]) - ord('a'), int(a[1]) - 1
    bx, by = ord(b[0]) - ord('a'), int(b[1]) - 1

    visited = [[False] * 8 for _ in range(8)]

    visited[ay][ax] = True

    queue = [(ax, ay, 0)]

    while queue:
        x, y, d = queue.pop(0)

        if x == bx and y == by:
            return d

        next_moves = [(x + dx, y + dy) for dx, dy in moves]

        next_moves = [(x, y) for x, y in next_moves
                      if x >= 0 and x < 8 and y >= 0 and y < 8]

        next_moves = [(x, y) for x, y in next_moves
                      if not visited[y][x]]

        for x, y in next_moves:
            visited[y][x] = True
            queue.append((x, y, d+1))
    return -1


def main():
    while True:
        try:
            x, y = input().split()
            print(f"To get from {x} to {y} takes", knight_moves(x, y), "knight moves.")
        except EOFError:
            break

if __name__ == "__main__":
    main()
