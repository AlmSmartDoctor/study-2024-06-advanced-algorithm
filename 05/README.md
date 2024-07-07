# Ch 19. 큐와 스택, 데크 & Ch 23. 우선순위 큐와 힙

> 발표일 `24.07.10`
>
> 발표자 `최준영`

# 19. 큐와 스택, 데크

## 19.1. 도입

- queue : FIFO
- stack : LIFO
- dequeue : queue + stack

- push, pop
  - O(1)

## 19.2. 큐와 스택, 데크의 구현

### 연결 리스트

- 양쪽 끝 요소 추가, 삭제 O(1)

### 동적 배열

| - | 1 | 2 | 3 | 4 | - | - | - | - | - |

| - | - | - | 3 | 4 | 5 | 6 | 7 | - | - |

- 맨 앞에서 원소를 꺼낼 때 뒤에 있는 원소들을 앞으로 당기는 대신 head를 다음 원소로 옮김

| 10| 11| - | 3 | 4 | 5 | 6 | 7 | 8 | 9 |

- 공간 재활용을 위해 circular buffer 사용

## 19.3. 스택과 큐의 활용

### 짝이 맞지 않는 괄호

- (), {}, [] - 모든 괄호는 짝을 이룬다.
- 서로 다른 괄호쌍이 교차해 있으면 안된다.

```
loop el in formula
  if opening.find(el) -> stack.push(el)
  else
    if stack.empty() -> return false
    if el is not matched to stack.top() -> return false
  stack.pop()
end
return stack.empty()
```

### 외계 신호 분석

- 길이가 N인 신호 기록이 주어질 때 합이 K인 부분 수열의 개수
- 1, 4, 2, 1, 4, 3
  - 1, 4, 2
  - 4, 2, 1
  - 2, 1, 4
  - 4, 3
- 조건
  - 10초
  - 64MB
- 입력
  - 테스트 케이스 수 1 <= C <= 20
  - 1 <= K <= 5,000,000
  - 1 <= N <= 50,000,000

#### 입력 크기 이슈

- 5000만개의 32bit 정수 -> 190MB > 64MB
- 5000만개의 16bit 정수 -> 95MB > 64MB

**온라인 알고리즘 도입**
전체 입력이 한꺼번에 주어지지 않아도 계산을 시작할 수 있는 알고리즘
알고리즘 수행 중 새 입력을 받아 계산을 이어나감

#### 오프라인 알고리즘

- 모든 부분 수열 순회

```
ret = 0;
for int head = 0; head < signals.size(); head++
  sum = 0;
  for tail = head; tail < signals.size(); tail++
  sum += signals[tail];
  if sum == k -> ret++
  if sum >= k -> break;
return ret
```

**다음 head의 tail은 이전 tail 값보다 줄어들 수 없다**

> 현재 tail을 현재 head부터 시작하지 않고 이전 tail부터 시작

```
ret = 0;
lastTail = 0;
for int head = 0; head < signals.size(); head++
  sum = 0;
  for tail = lastTail; tail < signals.size(); tail++
  sum += signals[tail];
  if sum == k -> ret++
  if sum >= k -> break;
return ret
```

이중 루프 때문에 O(N^2)으로 보일 수 있으나, tail은 최대 N번 순회하므로 O(N)

#### 온라인 알고리즘

```
RNG rng; // 신호 생성기
ret = 0, sum = 0;
for i = 0; i < N; i++
  newSignal = rng.next();
  sum += newSignal;
  queue.push(newSignal);
  while sum > k
    sum -= queue.front();
    queue.pop();
  if sum == k -> ret++;
return ret;
```

# 23. 우선순위 큐와 힙

## 우선순위 큐

우선 순위가 가장 높은 큐가 가장 먼저 꺼내짐
우선 순위로 정렬된 힙을 이용해 구현
가장 우선순위가 큰 노드만 찾으면 되기 때문에 이진 트리 사용할 필요 없음

## 힙

- 부모 노드 원소 >= 자식 노드 원소
- 마지막 레벨을 제외한 모든 레벨에 노드가 꽉 차 있어야 함.

### 원소 삽입

O(logN) (= 트리 높이)

```
heap.push_back(newValue);
idx = heap.size() - 1;
while idx > 0 && heap[(idx - 1) / 2] < heap[idx]
  swap(heap[idx], heap[(idx-1) / 2]);
  idx = (idx - 1) / 2;
```

> 힙의 가장 마지막 위치에 삽입하고 부모노드와 비교해서 부모 노드보다 작을 때까지 스왑

### 최대 원소 꺼내기

O(logN) (= 트리 높이)

```
heap[0] = heap.back();
heap.pop_back();
here = 0;
while 1
  left = here * 2 + 1, right = here * 2 + 2;
  if left >= heap.size() -> break;
  next = here;
  if heap[next] < heap[left]
    next = left;
  if right < heap.size() && heap[next] < heap[right]
    next = right;
  if next == here -> break;
  swap(heap[here], heap[next]);
  here = next;
```

> 힙의 마지막 원소를 최상위 노드에 넣고 정렬

### 변화하는 중간 값

- 3, 1, 5, 4, 2
  - 중간 값 = 3
- 수열 개수 = 짝수 일 때
  - 중간 두 값 중 작은 값 = 수열의 중간 값

수열의 절반은 maxHeap에 나머지 절반은 minHeap에 저장
수열의 길이가 홀수면 최대 힙에 숫자를 하나 더 저장

1. 최대 힙의 크기는 최소 힙의 크기와 같거나 1 더 크다
2. 최대 힙의 최대 원소는 최소 힙의 최소 원소보다 작거나 같다.

**수열의 중간 값은 항상 최대 힙의 루트에 있음**

```
RNG rng // 난수 생성
for int cnt = 0; cnt < n; cnt++
  if maxHeap.size() == minHeap.size()
    maxHeap.push(rng.next());
  else
    minHeap.push(rng.next());
  // 2번 조건이 깨졌을 때
  if !minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()
    a = maxHeap.top();
    b = minHeap.top();
    maxHeap.pop();
    minHeap.pop();
    maxHeap.push(b);
    minHeap.push(a);
return maxHeap.top();
```
