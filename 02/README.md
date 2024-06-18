# Ch 08. 동적 계획

> 발표일 `24.06.19`
>
> 발표자 `정예찬`

<br/>
<br/>

# 동적 계획법
<br/>
하나의 큰 문제를 여러 개의 작은 문제로 나누어서 그 결과를 저장하여 다시 큰 문제를 해결
<br/>
<br/>
큰 의미에서 분할 정복과 같은 접근 방식이다. 다른 부분은 문제를 나누는 방식 -> 어떤 부분 문제가 2개 이상의 문제를 푸는데 사용될 수 있음
<br/>
<br/>
이미 계산한 값을 저장해 드는 메모리의 장소 = 캐시 (cache)
<br/>
두번 이상 계산되는 부분 문제 = 중복되는 부분 문제 (overlapping subproblems)
<br/>
<br/><br/>

> "Memoization"

<br/><br/><br/>

## 동적 계획법을 이용한 이항계수 구하기
![Bino](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/168400038/22c85bc4-3871-4006-a795-bfb9f0bba06f)

<br/><br/><br/>

```
int bino(int n, int r) {
  if( r == 0 || n == r) return 1;
  return bino(n-1, r-1) + bino(n-1 + r)
}
```

<br/><br/>

### 중복 제거 전

![중복 제거 전](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/168400038/39154fa7-3f4c-4096-b0b5-bd6dc443d8dd)
<br/><br/>
### 중복 제거 후

![중복 제거 후](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/168400038/e32354a8-f866-499b-a278-eb453c374381)
<br/><br/>


```
int cache[30][30];
// -1 로 초기화
int bino(int n, int r){
  if(r == 0 || n == r) return 1;
  if(cache[n][r] != -1) return cache[n][r];
  return cache[n][r] = bino(n-1, r-1) + bino(n-1, r);
```

<br/><br/><br/><br/>

## 메모지제이션을 적용할 수 있는 경우

입력이 같은데도 외부 요소에 따라 다른 값이 반환된다면 캐싱을 할 수 없겠죠?
<br/>
함수의 반환 값이 그 입력 값 만으로 결정되는지 여부
-> 참조적 투명성 (referential transparency)

<br/>
<br/>

### 메모이제이션 구현 패턴

1. 기저 사례를 항상 먼저 처리한다
2. 함수의 반환 값을 이용하여 초기화 (ex. 항상 0 이상이라면 -1로 초기화)
3. 반환 값을 참조형으로 한다.
4. cahce 초기화 로직을 구현

<br/>
<br/>
<br/>

### 예제: 외발 뛰기
<br/>

![JUMPGAME](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/168400038/1701cca5-3838-4d42-b7d0-46b1323f3b49)
<br/>

왼쪽 위부터 시작해서 게임판의 맨 오른쪽 칸에 도달하는 법
<br/>
각 칸에 적혀있는 숫자만큼 아래나 오른쪽으로 이동할 수 있으며, 중간에 게임판 밖으로 벗어나면 안됨.
<br/>
시작점에서 끝점으로 도달하는 방법이 있는지 확인하는 문제
<br/>
<br/>

##### 재귀 호출에서 시작하기

<br/>
동적 계획법 알고리즘을 만드는 첫 단계는 해당 문제를 재귀적으로 해결하는 완전 탐색 알고리즘을 만드는 것.
```
int n, board[100][100];
bool jump(int y, int x) {
  if(y >= n || x >= n) return false;
  if(y == n-1 && x == n-1) return true;
  int jumpSize = board[y][x];
  return jump(y + jumpSize,x) || jump(y, x + jumpSize);
}
```
위 해결법의 문제점?
n에 대하여 지수적으로 늘어나는 경로의 갯수

<br/>
<br/>

외발 뛰기 문제를 해결하는 동적 계획법 알고리즘
```
int n, board[100][100];
int cache[100][100];
int jump(int y, int x) {
  if( y >= n || x >= n) return 0;
  if( y == n-1 && x == n-1) return 1;
  int& ret = cache[y][x];
  if(ret != -1) return ret;
  int jumpSize = board[y][x]
  return ret = jump(y + jumpSize, x) || jump(y, x + jumpSize);
}
```
<br/><br/>

### 동적 계획법 레시피

1. 주어진 문제를 완전 탐색을 이용하여 해결한다.
2. 중복된 부분을 한번만 계산하도록 메모이제이션을 적용한다.

<br/><br/><br/>

