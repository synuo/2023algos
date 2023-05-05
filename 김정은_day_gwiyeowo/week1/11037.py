def make_nls(mxlen: int, cnt: int, used: bin, val: int):
    if cnt >= mxlen:
        number_list.append(val)
    else:
        for i in range(9):
            if used & (1 << i):
                continue
            make_nls(mxlen, cnt + 1, used | (1 << i), val * 10 + numbers[i])


numbers = [i for i in range(1, 10)]
number_list = [0]
for i in range(1, 10):
    make_nls(i, 0, 0, 0)

while True:
    try:
        n = int(input())
        if n >= 987654321:
            print(0)
        else:
            start = 0
            end = len(number_list)
            while start + 1 < end:
                mid = (start + end) // 2
                if number_list[mid] <= n:
                    start = mid
                else:
                    end = mid
            if number_list[start] <= n:
                print(number_list[end])
    except EOFError:
        break
