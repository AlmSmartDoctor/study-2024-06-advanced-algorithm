# Ch 11. 조합 탐색

> 발표일 `24.06.26`
>
> 발표자 `서형석`

<br/>
<br/>

## 11.1 도입
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
- 문제를 n개의 선택지로 조각냈는데 각 선택지마다 3가지의 선택이 있다면 O(3^n)

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
## 11.2 조합 탐색 기법들

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

|최적화|소형(n=12)|중형(n=16)|(대형(n=20)|초대형(n=24)|
|------|---|---|---|---|
|동적계획법|0.03s|0.58s|26.45s|768.21s|


<br><br>
### 0. 조합 탐색의 뼈대 구현
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

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
없음(완전탐색)	|89.74초| TLE	|TLE	|TLE

<br><br>

### 1. 최적해보다 나빠지면 그만두기

```
// 간단한 가지치기: 지금까지 찾은 가장 좋은 답 이상일 경우 중단
if(best <= currentLength) return;
```

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
없음(완전탐색)	|89.74초| TLE	|TLE	|TLE
최적해보다 나빠지면그만두기	|2.58초|	981.53초|	TLE	|TLE


<br><br>

### 2. 간단한 휴리스틱을 이용한 가지치기


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
최적해보다 나빠지면그만두기	|2.58초|	981.53초|	TLE	|TLE
단순한 휴리스틱 |	0.85초	| 84.18초|	TLE	| TLE

<br><br>
### 3. 가까운 도시부터 방문하기

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

<br><br>

### 4. 지나온 경로를 이용한 가지치기

```
코드 11.4 지나온 경로를 이용하는 두 가지 가지치기 전략의 구현

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

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
가까운 도시부터 방문하기 |0.52초| 	31.03초| TLE | TLE
인접한 두 도시 순서 바꾸는 가지치기|	0.15초|	4.64초|	233.52초|	TLE
부분 경로 뒤집는 가지치기	|0.07초	|1.13초	|33.29초|	1160.81초

<br><br>

### 5.  MST 휴리스틱을 이용한 가지치기의 구현

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

<br><br>

### 6. 마지막 단계 메모이제이션하기

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

|최적화	|소형 (n = 12)|	중형 (n = 16)|	대형 (n = 20)	|초대형(n = 24)
| -- | -- | -- | -- | -- |
동적계획법 |	0.03초| 	0.58초|	26.45초	|768.21초
휴리스틱을 MST로 교체 |	0.06초 |	0.37초 | 	14.77초 | 	836.43초
메모이제이션	| 0.06초 | 	0.28초 | 	2.91초	| 25.24초


<br><br>


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