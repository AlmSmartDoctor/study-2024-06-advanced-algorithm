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

### 예제: 원주율 외우기

#### 문제:
<br/>
가끔 TV 에 보면 원주율을 몇만 자리까지 줄줄 외우는 신동들이 등장하곤 합니다. 이들이 이 수를 외우기 위해 사용하는 방법 중 하나로, 숫자를 몇 자리 이상 끊어 외우는 것이 있습니다. 이들은 숫자를 세 자리에서 다섯 자리까지로 끊어서 외우는데, 가능하면 55555 나 123 같이 외우기 쉬운 조각들이 많이 등장하는 방법을 택하곤 합니다.
<br/>
이 때, 각 조각들의 난이도는 다음과 같이 정해집니다:
<br/><br/>
모든 숫자가 같을 때 (예: 333, 5555) 난이도: 1
<br/>
숫자가 1씩 단조 증가하거나 단조 감소할 때 (예: 23456, 3210) 난이도: 2
<br/>
두 개의 숫자가 번갈아 가며 출현할 때 (예: 323, 54545) 난이도: 4
<br/>
숫자가 등차 수열을 이룰 때 (예: 147, 8642) 난이도: 5
<br/>
그 외의 경우 난이도: 10
<br/><br/>
원주율의 일부가 입력으로 주어질 때, 난이도의 합을 최소화하도록 숫자들을 3자리에서 5자리까지 끊어 읽고 싶습니다. 최소의 난이도를 계산하는 프로그램을 작성하세요.
<br/>

#### 풀이
##### 분할 정복으로 가능 한가?
<br/>
위 문제는 완전 탐색으로 세기가 절대 불가능 하다.
<br/>
길이가 7인 수열 1111222를 보면 이 수열을 쪼갤 수 있는 방법은 두 가지이다.
<br/>
{1111,222} 혹은 {111,1222}.
<br/>
따라서 길이 7인 수열이 n개 있으면 이들을 이렇게 쪼갤 수 있는 방법의 수는 2^n개가 된다.
<br/>
길이 10000인 수열에는 길이 7인 수열이 1,428개 들어갈 수 있다.
<br/>


<br/>
<br/>
##### 메모이제이션의 적용
<br/>
<br/>
다음 3가지로 나눌 수 있음
<br/><br/>
 - 길이 3인 조각의 난이도 + 나머지의 수열의 최적해
   <br/>
 - 길이 4인 조각의 난이도 + 나머지의 수열의 최적해
   <br/>
 - 길이 5인 조각의 난이도 + 나머지의 수열의 최적해
<br/><br/>

나머지 수열의 최적해를 구할 때 앞의 부분을 어떤 식으로 쪼갰는지는 중요하지 않음
<br/><br/><br/>
classify() = 구간의 난이도 반환
<br/>
memorize() = 부분 수열의 시작 begin이 주어졌을 때 최소 난이도를 반환
<br/>
```
int cache[10002];
int memorize(int begin) {
  if(begin == N.size()) return 0;
  int& ret = cache[begin];
  if(ret != -1) return ret;
  ref = INF;
  for(int L = 3; L <= 5; ++L)
    if(begin + L <= N.size())
      ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
  return ret;
}
```
<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>



