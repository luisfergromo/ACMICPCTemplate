namespace DLX {
const int MAXN = 1000;
const int MAXM = 400;
const int INF = 0x3f3f3f3f;
int D[MAXN * MAXM], U[MAXN * MAXM], L[MAXN * MAXM], R[MAXN * MAXM], COL[MAXN * MAXM], ROW[MAXN * MAXM];
int CNT, BEG[MAXN * MAXM], END[MAXN * MAXM], ANS, USE[MAXM], _USE[MAXM];
int SUM[MAXM];
bool vis[MAXM];
void init(int n) {
  memset(BEG, 0xff, sizeof(BEG));
  for(int i = 1; i <= n; i++)
    SUM[L[i + 1] = R[i - 1] = D[i] = U[i] = i] = 0;
  L[L[1] = R[n] = 0] = n, CNT = n + 1;
  ANS = n + 1;
}
void link(int r, int c) {
  D[CNT] = D[c], U[CNT] = c, U[D[c]] = CNT, D[c] = CNT, COL[CNT] = c, ROW[CNT] = r, SUM[c]++;
  if (BEG[r] == -1) BEG[r] = END[r] = CNT;
  R[END[r]] = CNT, L[CNT] = END[r], R[CNT] = BEG[r], L[BEG[r]] = CNT, END[r] = CNT++;
}
void DLX_Remove_Repeat(int c) {
  for (int i = D[c]; i != c; i = D[i])
    L[R[i]] = L[i], R[L[i]] = R[i], SUM[COL[i]]--;
}
void DLX_Resume_Repeat(int c) {
  for (int i = U[c]; i != c; i = U[i])
    L[R[i]] = i, R[L[i]] = i, SUM[COL[i]]++;
}
int Heuristics() {
  memset(vis, true, sizeof(vis));
  int c, i, j, cnt=0;
  for(c=R[0]; c; c=R[c])
    if(vis[c])
      for(cnt++, vis[c] = false, i = D[c]; i != c; i = D[i])
        for(j = R[i]; j != i; j = R[j])
          vis[COL[j]] = false;
  return cnt;
}
void DLX_Dfs(int n) {
  if (Heuristics() + n >= ANS) return;
  if (R[0] == 0) {
    ANS = n;
    for (int i = 0; i < n; i++)
      USE[i] = _USE[i];
    return ;
  }
  int i,now = INF,c;
  for (i = R[0]; i; i = R[i])
    if (now > SUM[i])
      now = SUM[c = i];
  for(i = D[c]; i != c; i = D[i]) {
    DLX_Remove_Repeat(i);
    for(int j = R[i]; j != i; j = R[j])
      DLX_Remove_Repeat(j);
    _USE[n] = ROW[i];
    DLX_Dfs(n + 1);
    for(int j = L[i]; j != i; j = L[j])
      DLX_Resume_Repeat(j);
    DLX_Resume_Repeat(i);
  }
}
void solve() {
  //ANS = m
  DLX_Dfs(0);
}
};
