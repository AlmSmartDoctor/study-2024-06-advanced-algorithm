# Ch 11. 조합 탐색

> 발표일 `24.06.26`
>
> 발표자 `서형석`

<br/>
<br/>

# 11.1 도입
<br>

앞서 살펴본 문제 해결 패러다임 Divide & Conquer, Dynamic Programming은 만능이 아님
- 적절한 분할 방법이 없다면 Divide & Conquer 사용 불가
- overlapping subproblem이 없거나 memory를 너무 많이 사용하면 Dynamic Programming 사용 불가

이럴 땐 시작점인 완전 탐색으로 돌아가야 함
- 답을 만드는 과정을 여러 선택으로 나누고
- 재귀 호출을 이용해 각각의 선택지를 채워가는 형태

*탐색 공간(Search Space):*
> 부분 답과 완성된 답의 집합

ex) 외판원 문제(Traveling salesman problem)의 탐색 공간: 지금까지 방문한 정점의 목록과 현재 위치의 집합

<br>

### 완전 탐색(Exhaustive Search)의 문제
> 문제의 규모가 크면 사용하기 어렵다

- 수행 시간이 탐색 공간의 크기에 비례하는데, 탐색 공간은 규모에 따라 기하급수적으로 증가
- 문제를 n개의 선택지로 조각냈는데 각 선택지마다 3가지의 선택이 있다면 $O(3^n)$

<br>

### 조합 탐색
> 유한한 크기의 탐색 공간을 뒤지며 답을 찾아내는 알고리즘

- 최적해가 될 가능성이 없는 답을 탐색하는걸 방지해 만들어야 할 답의 수를 줄이는 걸 목표로 함

<br>

### 조합 탐색 기법 분류
1. 가지치기(pruning):
    > 탐색 과정에서 최적해로 연결될 가능성이 없는 부분들을 잘라냄
    - 지금까지 찾아낸 최적해보다 부분해가 더 나쁘다면 더이상 탐색하지 않아도 됨
    - 존재하는 답 중 일부는 아예 만들지 않으므로 동작 속도가 빨라짐

2. 좋은 답을 빨리 찾아내는 기법:
    > 탐색의 순서를 바꾸거나, 탐색 시작 전 탐욕법을 이용해 적당히 좋은 답을 우선 찾아냄
    - 가지치기와 함께 사용할 경우 더 좋은 답을 일찍 알수록 탐색을 더 빨리 중단할 수 있으므로 효율이 좋아짐
<br>

![image](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/66310634/59f1d24d-9c0a-4258-8f94-1997109c558d)

(a): 맨 왼쪽 답을 찾은 이후엔 그 이상 깊이 탐색하지 않음

(b): 가운데 답을 적절한 탐욕법이나 휴리스틱을 이용해 먼저 찾는다면, 깊이 6이하로 내려갈 필요가 없어 더 적은 상태만을 검사하고 최적해를 찾아낼 수 있음



<br/><br/>
# 11.2 조합 탐색 기법들

'대표적인 최적화 문제인 TSP를 푸는 완전 탐색 알고리즘에 조합 탐색 기법을 적용, 변화하는 수행 속도를 관찰'

### 테스트 환경
- Ubuntu Linux 10.04
- g++ 4.4.3 (컴파일 옵션 -O3)
- 인텔 Core i7 920 (2.67GHz). RAM 9GB


### 입력 파일
- 소형, 중형, 대형, 초대형의 네 가지 입력
- 각 입력은 2차원 평면에 N개의 점을 임의로 배치하고 이들 사이의 거리를 측정
- 각 입력당 수행 시간이 30분을 넘어가면 강제 종료


> 목표: 동적 계획법 알고리즘보다 더 빨리 답을 얻는 것

```
코드 9.15 여행하는 외판원 문제를 해결하는 동적 계획법 알고리즘

int n, dist[MAX][MAX];
double cache[MAX][1<<MAX]; // -1로 초기화해 둔다

// here: 현재 위치
// visited: 각 도시의 방문 여부
// here에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다
// 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다
// 항상 0번 도시에서 시작한다고 가정한다
double shortestPath2(int here, int visited) {

	// 기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다
	if(visited == (1<<n)-1) return dist[here][0];

	// 메모이제이션
	double& ret = cache[here][visited];

	if(ret >= 0) return ret;
	ret = INF; // 매우 큰 값으로 초기화

	// 다음 방문할 도시를 전부 시도해 본다.
	for(int next = 0; next < n; ++next) {
		// 이미 방문한 도시인 경우
		if(visited & (1<<next)) continue;
		double cand = dist[here][next] + shortestPath2(next, visited + (1<<next));
		ret = min(ret, cand);
	}
	return ret;
}
```

|최적화|소형(n=12)|중형(n=16)|(대형(n=20)|초대형(n=24)|
|------|---|---|---|---|
|동적계획법|0.03s|0.58s|26.45s|768.21s|

- 입력이 커질수록 수행 시간이 급격히 증가
- 메모리 또한 입력 크기에 따라 지수적으로 증가. 초대형 입력을 처리하기 위해 약 3GB 메모리 필요. 메모리가 모자랐다면 가상 메모리를 사용했을 것이고, 매우매우 느려졌을 것.

<br><br>
## 0. 조합 탐색의 뼈대 구현
```
코드 11.1 TSP를 해결하는 완전 탐색의 구현

const double INF = 1e200;
const int MAX = 30;

int n; // 도시의 수
double dist[MAX][MAX]; // 두 도시간의 거리를 저장하는 배열

// 지금까지 찾은 최적해
double best;

// path: 지금까지 만든 경로
// visited: 각 도시의 방문 여부
// currentLength: 지금까지 만든 경로의 길이
// 나머지 도시들을 모두 방문하는 경로들을 만들어 보고 가능하면 최적해를 갱신한다.
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	int here = path.back();

	// 기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다.
	if(path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}

	// 다음 방문할 도시를 전부 시도
	for(int next = 0; next < n; ++next) {
		if(visited[next]) continue;
		path.push_back(next);
		visited[next] = true;

		// 나머지 경로를 재귀 호출을 통해 완성
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

double solve() {
	// best를 매우 큰 값으로 초기화
	best = INF;

	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}
```

수행 속도
- 찾아야 할 경로의 첫 도시는 항상 0으로 고정했기 때문에 $search()$가 만드는 경로의 수는 $(n-1)!$개 
- 11!는 약 4천만 정도 되는 수이므로, 소형 입력은 그럭저럭 풀 수 있음, 단 중형 입력에서 경로의 개수는 $12 \times 13 \times 14 \times 15 \approx 30,000$배 늘기 때문에 중형 입력을 풀기란 불가능

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
없음(완전탐색)	|89.74초| TLE	|TLE	|TLE

소형 입력이 약 90초. 중형 입력은 4만 5천 분(750시간) 소요.

#

<br><br>

## 1. 최적해보다 나빠지면 그만두기

<br>
가장 기초적인 가지치기 방법

> 현재 상태의 답이 지금까지 구한 최적해와 같거나 더 나쁠 때 탐색을 중단


- 다음 한 줄을 search() 함수의 처음에 추가

```
// 간단한 가지치기: 지금까지 찾은 가장 좋은 답 이상일 경우 중단
if(best <= currentLength) return;
```

최소한 현재 경로의 길이가 지금까지 가지고 있는 최적해보다 커졌을 때는 탐색을 종료. N!개의 경로를 전부 만들지 않음.


|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
없음(완전탐색)	|89.74초| TLE	|TLE	|TLE
최적해보다 나빠지면그만두기	|2.58초|	981.53초|	TLE	|TLE

소형 입력 데이터를 해결하는 데 걸리는 시간이 30분의 1로 줄어듬


<br><br>

## 2. 간단한 휴리스틱을 이용한 가지치기
<br>

조합 탐색에서 방문하는 상태의 수는 탐색의 깊이가 깊어질수록 증가하기 때문에, 
탐색 중 ‘이 부분에서는 최적해가 나올 수 없다’는 것을 가능한 한 일찍 알아내는 것이 유리.

TSP를 예로 들면
- 방문할 도시가 5개 남은 시점 탐색을 중단하면 5! = 120개의 경로를 만드는 시간을 절약
- 방문할 도시가 10개 남은 시점 탐색을 중단하면 10! = 3628800개의 경로를 만드는 시간 절약

#### 휴리스틱(heuristic)을 이용한 가지치기

> 남은 조각들을 푸는 최적해를 찾기는 오래 걸리더라도, 이 값을 적당히 어림짐작하기는 훨씬 빠르게 할 수 있다는 점을 이용해 가지치기를 수행

![image](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/66310634/dfe2d921-9392-4654-a8a9-10ba405754a6)
- 그림 (a)에서는 아직 방문하지 않은 도시들이 서로 멀찍이 떨어져 있고
- 그림 (b)에서는 이들이 상대적으로 가까울 뿐더러, 간단한 경로로 이들을 다 거쳐 시작점으로 돌아갈 수 있다

아직 방문하지 않은 도시의 수는 같아도, (a)와 (b)중 어느 쪽 경로의 남은 부분이 짧을지를 짐작하기란 어렵지 않다

<br>
이때 휴리스틱의 반환 값은 항상 남은 최단 경로의 길이 보다 작거나 같아야 한다.

- 휴리스틱이 실제 필요한 경로보다 더 긴 경로가 필요하다고 잘못 짐작하면, 최적해를 찾을 수 있는 상태를 걸러낸다
- 이런 방법들의 문제를 과소평가(Underestimate)하는 휴리스틱 or 낙관적인 휴리스틱(Optimisitic heuristic)이라고 한다.
- 따라서 **실제 답 이하이면서도 가능한 한 큰 값을 구해야 함**

<br>

휴리스틱 함수 작성 방법
> 문제의 제약 조건을 일부 없앤 더 단순한 형태의 문제를 구한다
- case 1. 남은 도시를 모두 방문할 필요 없이, 가장 멀리 있는 도시 하나만 방문했다가 시작점으로 돌아간다
- case 2. 남은 도시들을 방문하는 방법이 꼭 일렬로 연결된 형태가 아니어도 된다

<br>

단순한 휴리스틱 함수 구현

> 아직 방문하지 않은 도시들에 대해 인접한 간선 중 가장 짧은 간선의 길이를 더한다
- 아직 방문하지 않은 도시를 방문하려면 인접한 간선 중 하나를 타고 가야 하므로, 이들 중 가장 짧은 간선의 길이를 모으면 실제 최단 경로 이하의 값이 될 수밖에 없음

```
코드 11.2 단순한 휴리스틱을 이용한 가지치기의 구현

// 각 도시에 인접한 간선 중 가장 짧은 것을 미리 찾아 둔다.
double minEdge[MAX];

// 가장 단순한 형태의 휴리스틱
double simpleHeuristic(vector<bool>& visited) {
	double ret = minEdge[0]; // 마지막에 시작점으로 돌아갈 때 사용할 간선
	for(int i = 0; i < n; ++i)
		if(!visited[i])
			ret += minEdge[i];
	return ret;
}

void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	// 단순한 휴리스틱을 이용한 가지치기
	if(best <= currentLength + simpleHeuristic(visited)) return;

	// .. 생략 ..
}

double solve() {
	// simpleHeuristic()을 위한 초기화
	for(int i = 0; i < n; ++i) {
		minEdge[i] = INF;
		for(int j = 0; j < n; ++j)
			if(i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
	}

	// .. 생략 ..
}
```

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
없음(완전탐색)	|89.74초| TLE	|TLE	|TLE
최적해보다 나빠지면 그만두기	|2.58초|	981.53초|	TLE	|TLE
단순한 휴리스틱 |	0.85초	| 84.18초|	TLE	| TLE

- 중형 입력의 수행 시간이 최적해보다 나빠지면 그만두기보다 열배 넘게 빨라짐
- 소형 입력의 수행 시간은 완전 탐색보다 백 배 넘게 빨라짐

<br><br>
## 3. 가까운 도시부터 방문하기

<br>

TSP를 해결하는 조합 탐색은 각 재귀 호출마다 다음에는 어느 도시를 방문할지를 결정하는 방식으로 구현됨
> 이때 도시를 번호 순서대로 방문하는 대신, 더 가까운 것부터 방문하면 좋은 답을 더 빨리 찾아낼 수 있는 경우가 존재

![image](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/66310634/81228829-c195-4e60-a8bc-de9086d15407)

- 항상 최적해를 주진 않지만, 어느 정도 좋은 답을 좀더 일찍 발견할 확률이 올라갈 것. 그럼 가지치기를 더 많이 할 수 있음

```
코드 11.3 가까운 정점부터 방문하는 최적화의 구현

// 각 도시마다 다른 도시들을 가까운 순서대로 정렬해 둔다.
vector<int> nearest[MAX];
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	// .. 생략 ..

	// 다음 방문할 도시를 전부 시도해 본다.
	for(int i = 0; i < nearest[here].size(); ++i) {
		int next = nearest[here][i];

		// .. 생략 ..
	}
}

double solve() {
	// nearest 초기화
	for(int i = 0; i < n; ++i) {
		vector<pair<double, int> > order;
		for(int j = 0; j < n; ++j)	
			if (i != j)
				order.push_back(make_pair(dist[i][j], j));
		sort(order.begin(), order.end());
		nearest[i].clear();
		for(int j = 0; j < n-1; ++j)
			nearest[i].push_back(order[j].second);
	}

	// .. 생략 ..
}
```
|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
단순한 휴리스틱 |	0.85초	| 84.18초|	TLE	| TLE
가까운 도시부터 방문하기 |0.52초| 	31.03초| TLE | TLE
- 중형 입력의 수행 시간이 꽤 빨라짐
- 탐색을 시작하기 전에 탐욕적 알고리즘으로 초기해를 구하는 것과 같은 효과
	- 항상 방문하지 않은 도시 중 가장 가까운 쪽으로 가는 탐욕적 알고리즘의 답을 항상 맨 처음에 찾게 되기 때문


<br><br>

## 4. 지나온 경로를 이용한 가지치기

<br>

> 지금까지 만든 부분 답을 검사해서 가지치기를 할 수도 있다
- 지금까지 만든 경로가 시작 상태에서 현재 상태까지 도달하는 최적해가 아니라면 앞으로 남은 조각들에서 최적해를 찾을 수 없고, 탐색을 계속할 이유가 없다.

<br>

![image](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/66310634/9b061d3c-e2f6-4a94-9f5a-5a14d9bd8635)
- (a)에서 세 번쨰와 네 번째 방문 도시의 순서를 바꾸면 (b)가 됨
- 현재 위치도 같고, 아직 방문하지 않은 도시들의 집합도 같으니 남은 조각들의 최소 비용은 똑같으나, **(b)의 경로가 (a)의 경로보다 더 짧음**

<br>

물론 현재 상태까지 오기 위해 택한 경로가 최적해인지를 알기 쉽지 않음
> 대개 지나간 길을 돌아보는 가지치기는 **탐색의 각 단계에서 현재까지 만든 부분해에 간단한 조작을 가하고**, 결과적으로 **답이 더 좋아진다면 탐색을 중단**

TSP에서는 **두 개의 인접한 도시를 골라서 이 둘의 순서를 바꿔 본 뒤, 경로가 더 짧아지면 탐색을 중단**하는 가지치기를 구현

- 지금까지 만든 경로가 다음과 같은 형태라고 하자.
    
    ( … , … , p, a, b, q, … , here)
    
- 이 경로에서 $a$와 $b$의 순서를 바꿔 $p-q$구간의 거리가 더 짧아진다면, 이 경로에서 최적해를 찾을 가능성이 없으니 탐색을 중단

<br>

```
코드 11.4.1 지나온 경로를 이용하는 두 가지 가지치기 전략의 구현

// path의 마지막 네 개의 도시 중 가운데 있는 두 도시의 순서를 바꿨을 때
// 경로가 더 짧아지는지 여부를 반환한다
bool pathSwapPruning(const vector<int>& path) {

	if(path.size() < 4) return false;

	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];

	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
```
search()의 처음에 pathSwapPruning()을 수행해보고 참이 돌아오면 탐색을 종료
- 반복문을 돌면서 모든 도시 쌍을 뒤집어 보는 것이 아니라, 항상 현재 도시 이전의 두 도시만을 뒤집어 본다는 것에 유의. 한 도시를 경로 뒤에 추가할 때마다 pathSwapPruning() 이 수행되기 때문.
- **실질적으로 탐색 공간의 크기를 절반 이하로 줄여 주는 효과가 있음**. 마지막 세 도시의 순서가 a, b, c인 경로와 b, a, c인 경로 중 더 짧은 것만을 탐색하기 때문


<br>

pathSwapPruning()을 좀 더 일반화하면 더 나은 성능을 얻을 수 있다.
> 두 도시의 순서를 바꾸는 대신, 전체 경로의 일부분을 통째로 뒤집는 것
- 지금까지 방문한 도시의 순서가 다음과 같다고 하면 (…, p, a, b, c, d, e, q, …, here)
- 길이 5인 부분 경로 (a, b, c, d, e)를 뒤집으면 다음과 같음 (…, p, e, d, c, b, a, q, …, here)

이 경로가 원래 경로보다 더 짧아진다면 가지치기를 할 수 있음
- 이때 (a, b, c, d, e)나 (e, d, c, b, a)나 경로 자체의 길이는 똑같기 때문에, 달라지는 것은 $p$와 $q$에 인접하는 도시 뿐

```
코드 11.4.2 지나온 경로를 이용하는 두 가지 가지치기 전략의 구현
// 시작 도시와 현재 도시를 제외한 path의 부분 경로를
// 뒤집어 보고 더 짧아지는지 확인한다
bool pathReversePruning(const vector<int>& path) {

	if(path.size() < 4) return false;

	int b = path[path.size() - 2];
	int q = path[path.size() - 1];

	for(int i = 0; i + 3 < path.size(); ++i) {
		int p = path[i];
		int a = path[i+1];

		// [.., p, a, ..., b, q]를 [.., p, b, ..., a, q]로 바꿔본다
		if(dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
			return true;
	}
	return false;
}
```

<br>



> 2차원 평면의 TSP 경로가 자기 자신을 교차하면 이 답은 항상 최적이 아니다.

![image](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/66310634/617cb2b9-2873-4ce3-9f4a-6fcc683d73e2)

- (a)는 ((path[i], path[i+1])와 (path[j], path[j+1])가 교차하는 경로
	- 교차하는 두 화살표 대신 점선으로 표시된 두 선을 사용하면 전체 경로의 길이가 더 짧아짐
- (b)는 이 점선으로 표시된 선을 사용해 경로를 더 짧게 한 결과
	- path[i+1]에서 path[j]까지의 구간의 순서가 뒤집힘

경로의 일부분을 뒤집었을 때 더 짧아지지 않는다 -> 이 경로가 자기 자신과 교차하지 않음을 보장


pathSwapPruning() 은 길이 2인 경로들을 모두 뒤집어 보는 것이고, pathReversePruning()은 모든 길이의 부분 경로를 뒤집어 보기 때문에 이전 방법보다 더 많은 경우를 가지치기할 수 있을 거라고 예측할 수 있음

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
가까운 도시부터 방문하기 |0.52초| 	31.03초| TLE | TLE
인접한 두 도시 순서 바꾸는 가지치기|	0.15초|	4.64초|	233.52초|	TLE
부분 경로 뒤집는 가지치기	|0.07초	|1.13초	|33.29초|	1160.81초

- 이 두 가지치기는 우리가 대형과 초대형 입력을 시간 내에 풀 수 있도록 해줌
- 특히 부분 경로 뒤집는 가지치기는 거의 동적 계획법과 비슷한 수준의 속도를 보여줌. 중형 입력은 약 1초만에 풀 수 있는데, 완전 탐색이 약 750시간 정도 걸릴 거라고 예측했던 것에 비하면 정말 엄청난 발전

<br><br>

## 5.  MST 휴리스틱을 이용한 가지치기의 구현

<br>

비교적 간단한 최적화는 거의 다 했으므로 더 나은 휴리스틱 알고리즘을 고민
> 앞에서 다룬 단순한 휴리스틱도 그럴듯한 답을 주지만, 문제의 제약을 너무 많이 없애 답을 너무 과소평가한다

![image](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/66310634/d7084353-dce6-47fe-a588-3481f043c5d3)

- 짙은 회색으로 표시된 간선들이 단순한 휴리스틱이 선택하는 간선
- 얇은 간선은 한 번, 굵은 간선은 두 번 선택된 간선. 많은 간선들이 두 번 선택되므로 간선들이 하나로 연결되지도 않고 따로 따로 떨어져 있음

### 최소 스패닝 트리 활용
- 현재 위치에서 시작해서 아직 방문하지 않은 정점들을 모두 방문하고, 시작점으로 돌아오는 최단 경로는 스패닝 트리
- 최소 스패닝 트리의 가중치의 합은 항상 최단 경로보다 작음
- 크루스칼의 스패닝 트리 알고리즘으로 MST를 구하고 간선 가중치의 합에서 탐색의 하한 값을 예상


```
코드 11.5 MST 휴리스틱의 구현

// 상호 배타적 집합 자료 구조를 구현
struct DisjointSet {
	// n개의 원소로 구성된 집합 자료 구조를 만듦
	DisjointSet(int n);
	// here가 포함된 집합의 대표를 반환
	int find(int here);
	// a가 포함된 집합과 b가 포함된 집합을 합침
	bool merge(int a, int b);
};

// 모든 도시 간의 도로를 길이 순으로 정렬해 저장해 둔다.
vector<pair<double, pair<int, int> > > edges;

// here와 시작점, 아직 방문하지 않은 도시들을 모두 연결하는 MST를 찾는다
double mstHeuristic(int here, const vector<bool>& visited) {
	// Kruskal's MST
	DisjointSet sets(n);
	double taken = 0;

	for(int i = 0; i < edges.size(); ++i) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if(a != 0 && a != here && visited[a]) continue;
		if(b != 0 && b != here && visited[b]) continue;
		if(sets.merge(a, b))
			taken += edges[i].first;
	}
	return taken;
}

double solve() {
	// edges 초기화
	edges.clear();
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));

	sort(edges.begin(), edges.end());
	// .. 생략 ..
}
```
|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
부분 경로 뒤집는 가지치기	|0.07초	|1.13초	|33.29초|	1160.81초
휴리스틱을 MST로 교체 |	0.06초 |	0.37초 | 	14.77초 | 	836.43초

- 처음으로 동적 계획법보다 빠르게 동작하는 알고리즘이 나옴
- mstHeuristic()은 simpleHeuristic() 보다 수행하는 데 훨씬 많은 시간을 요구되나, 결과적으로 프로그램이 훨씬 빨라졌으니 **가지치기로 절약한 시간이 MST 계산에 드는 시간보다 훨씬 컸음을 알 수 있다**

<br><br>

## 6. 마지막 단계 메모이제이션하기

<br>

조합 탐색 과정에서 같은 상태를 두 번 이상 맞닥뜨리는 것은 흔하다
![image](https://github.com/AlmSmartDoctor/study-2024-06-advanced-algorithm/assets/66310634/9b061d3c-e2f6-4a94-9f5a-5a14d9bd8635)
- 그림 11.5의 두 경로는 TSP를 조합 탐색으로 풀 때 같은 상태를 두 개 이상의 방법으로 방문할 수 있음을 보여줌
- 이런 비효율을 메모이제이션으로 제거

대부분의 경우 메모이제이션을 그냥 사용하기에는 메모리가 부족할 것이므로, 남은 조각의 수가 미리 정해둔 수 $k$이하일 때만 메모이제이션을 수행
- TSP의 경우 5개 이하 도시가 남았을 때만 메모이제이션 
- 도시의 수가 20일 떄 그냥 동적 계획법을 하면 약 2천만 개의 상태를 저장.
- 마지막 5단계만 하면 44만 개의 상태만 저장.
	- $20 \times (\binom{20}{5} + \binom{20}{4} + \binom{20}{3} + \binom{20}{2} + \binom{20}{1}) \approx 440,000$
- 마지막 5개의 도시를 배치하는 문제를 $5!=120$번 푸는 대신에 한 번만 풀게 되니 탐색 속도가 최대 120배 빨라질 수 있음

<br>

> 단 이와 같은 이득을 쉽게 얻을 수는 없음. 가지치기를 사용하는 함수는 쉽게 메모이제이션할 수 없기 때문

- 메모이제이션을 하기 위해서는 함수의 반환 값이 현재의 상태에만 영향을 받아야 하는데, 가지치기를 적용하면 현재 상태까지 오기 위한 경로에 따라 반환 값이 달라질 수 있음
- 물론 경로까지 메모이제이션의 키로 사용하면 답이 틀리지는 않겠지만, 경로들은 서로 겹치지 않기 때문에 메모이제이션을 쓰는 의미가 없음.

> 따라서 이 방법을 이용하기 위해서는 가지치기를 사용하지 않는 동적 계획법 함수를 별도로 작성한 뒤, 마지막 $k$단계에 도달하면 이 함수를 사용하도록 구현

```
코드 9.15 여행하는 외판원 문제를 해결하는 동적 계획법 알고리즘

int n, dist[MAX][MAX];
double cache[MAX][1<<MAX]; // -1로 초기화해 둔다

// here: 현재 위치
// visited: 각 도시의 방문 여부
// here에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다
// 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다
// 항상 0번 도시에서 시작한다고 가정한다
double shortestPath2(int here, int visited) {

	// 기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다
	if(visited == (1<<n)-1) return dist[here][0];

	// 메모이제이션
	double& ret = cache[here][visited];

	if(ret >= 0) return ret;
	ret = INF; // 매우 큰 값으로 초기화

	// 다음 방문할 도시를 전부 시도해 본다.
	for(int next = 0; next < n; ++next) {
		// 이미 방문한 도시인 경우
		if(visited & (1<<next)) continue;
		double cand = dist[here][next] + shortestPath2(next, visited + (1<<next));
		ret = min(ret, cand);
	}
	return ret;
}
```

```
코드 11.6 부분적으로 메모이제이션을 사용하는 최적화의 구현

// 남은 도시의 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다
const int CACHED_DEPTH = 5;

// dp(here, visited) = cache[here][남은 도시의 수][visited]
map<int, double> cache[MAX][CACHED_DEPTH + 1];

// here: 현재 위치
// visited: 각 도시의 방문 여부
// 일 때, 나머지 도시를 모두 방문하고 시작점으로 돌아가는 최단 경로의 길이를 반환한다
double dp(int here, int visited) {

	// 기저 사례: 더 방문할 도시가 없으면 시작점으로 돌아간다
	if(visited == (1<<n)-1) return dist[here][0];

	// 메모이제이션
	int remaining = n - __builtin_popcount(visited);
	double& ret = cache[here][remaining][visited];
	if(ret > 0) return ret;
	ret = INF;

	// 다음 도시를 하나씩 시도한다
	for(int next = 0; next < n; ++next) {
		if(visited & (1<<next)) continue;
		ret = min(ret, dp(next, visited + (1<<next)) + dist[here][next]);
	}
	return ret;
}

void search(vector<int>& path, int visited, double currentLength) {

	// 기저 사례: 남은 도시 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다
	if(path.size() + CACHED_DEPTH >= n) {
		best = min(best, currentLength + dp(path.back(), visited));
		return;
	}

	// .. 생략 ..
}

double solve() {
	// .. 생략 ..

	// cache 초기화
	for(int i = 0; i < MAX; ++i)
		for(int j = 0; j <= CACHED_DEPTH; ++j)
			cache[i][j].clear();

// .. 생략 ..
}
```
동적 계획법으로 TSP를 푸는 ShortestPath2()와 비교 
1. shortestPath2() 가 사용하는 캐시는 배열이었지만, dp() 는 연관 배열인 $map$을 사용. 5개 이하의 도시가 남아 있을 경우 현재 위치와 $visited$ 의 조합의 수는 $24 \times \binom{24}{5} \approx 1,000,000$개밖에 되지 않는데, 배열을 쓰자면 $24 \times 2^{24}$개의 원소를 잡아야 함

2. shortestPath2() 에서는 cache 가 2차원 배열이었지만 dp() 에서 cache 는 현재 위치, 남은 정점의 수를 인덱스로 갖는 $map$의 2차원 배열로, 사실상 3차원 배열이다. $map$에 접근하는 비용은 원소의 수가 커지면 커질수록 늘어나므로, 남은 도시의 수별로 $map$을 나누면 접근하는 데 드는 시간을 조금이나마 줄이는 효과가 있다.

그 외에 볼 부분
-  $visited$가 불린 값의 배열이 아니라 정수
- $\_\_builtin\_popcount() $: g++ 내장 함수로, 주어진 숫자의 이진수 표현에서 1의 개수를 셈. 반환 값은 지금까지 방문한 도시의 수

<br>

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
휴리스틱을 MST로 교체 |	0.06초 |	0.37초 | 	14.77초 | 	836.43초
메모이제이션	| 0.06초 | 	0.28초 | 	2.91초	| 25.24초
- 메모이제이션은 입력의 크기가 크면 커질수록 큰 효과를 보여줌 초대형 입력은 무려 서른 배 넘게 빨라짐
- 마지막 다섯 단계를 계산하지 않음으로 인해 절약하는 시간은 $n$이 클수록 클테니 당연한 결과


<br><br>

### 동적 계획법으로 전환하는 시점
- CACHED_DEPTH를 실험을 통해 얻어 상수로 지정
- 이 값이 크면 클수록 더 많은 상태를 메모이제이션하겠지만, 원소가 많아지면 많아질수록 $map$에 접근하는 비용이 늘어남

<br>

### 최종 비교

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
| 0. 없음(완전탐색)	|89.74초| TLE	|TLE	|TLE
| 1. 최적해보다 나빠지면그만두기	|2.58초|	981.53초|	TLE	|TLE
| 2. 단순한 휴리스틱 |	0.85초	| 84.18초|	TLE	| TLE
| 3. 가까운 도시부터 방문하기 |0.52초| 	31.03초| TLE | TLE
| 4-1. 인접한 두 도시 순서 바꾸는 가지치기|	0.15초|	4.64초|	233.52초|	TLE
| 4-2. 부분 경로 뒤집는 가지치기	|0.07초	|1.13초	|33.29초|	1160.81초
| 5. 휴리스틱을 MST로 교체 |	0.06초 |	0.37초 | 	14.77초 | 	836.43초
| 6. 메모이제이션	| 0.06초 | 	0.28초 | 	2.91초	| 25.24초
- 약 750시간 걸릴 거라고 전망했던 중형 입력의 수행 시간이 0.28초까지 거의 1천만 분의 1로 줄어듬
- 처음에는 동적 계획법과 비교도 할 수 없이 느렸던 코드가 동적 계획법보다 최대 서른 배 가까이 빠르게 동작



<br><br>

### 전문적 TSP 해결 기법들
이 절에서는 TSP뿐만이 아니라 다른 문제에도 사용할 수 있는 일반적인 기법들만을 소개함. TSP를 푸는 최적의 방법과는 거리가 멈.

실제로 TSP만을 해결하기 위해 고안된 프로그램들은 정수 계획법(Integer Programming, IP)을 사용.

정수 계획법은 최적화 이론에서는 유명한 문제인 선형 계획법(Linear Programming, LP)의 일종. 다항 시간에 푸는 알고리즘은 아직 없지만 좀더 효율적으로 해결하기 위한 다양한 연구가 이루어져 있음.

- 실제로 1954년에 IP를 이용해 TSP를 처음으로 푼 논문에서는 49개의 도시에 대한 답을 제시. 우리가 이 절에서 24개의 도시를 갖는 입력을 갖고 끙끙댄 것에 비하면 매우 인상적




<br><br>

### 더 읽을거리

**Artificial Intelligence: A Modern Approach**

- 조합 탐색은 초창기 인공지능 분야에서 많이 연구되어서, 조합 탐색을 잘 설명한 인공지능 교과서들이 많음.
- 가장 유명한 인공지능 교과서 중 하나인 이 책에는 이 장에서 다룬 모든 알고리즘들이 잘 설명되어 있으며, 이들을 구현한 자바, 파이썬 소스코드도 제공됨.