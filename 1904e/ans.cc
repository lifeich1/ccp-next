// LUOGU_RID: 151903163
#include<bits/stdc++.h>
using namespace std;const int N=200010;
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
int n,m,dn,in[N],out[N],dep[N],ans[N],nxt[N],mx[N<<3],laz[N<<3];
vector<int>e[N],q[N],que[N];
void tag(int x,int v){laz[x]+=v;mx[x]+=v;}
void down(int x){if(laz[x])tag(x<<1,laz[x]),tag(x<<1|1,laz[x]),laz[x]=0;}
void modify(int x,int L,int R,int l,int r,int v){
	if(l<=L&&R<=r)return tag(x,v);down(x);
	int mid=L+R>>1;if(l<=mid)modify(x<<1,L,mid,l,r,v);if(r>mid)modify(x<<1|1,mid+1,R,l,r,v);
	mx[x]=max(mx[x<<1],mx[x<<1|1]);
}
int query(int x,int L,int R,int l,int r){
	if(l<=L&&R<=r)return mx[x];down(x);int mid=L+R>>1,res=0;
	if(l<=mid)res=max(res,query(x<<1,L,mid,l,r));
	if(r>mid)res=max(res,query(x<<1|1,mid+1,R,l,r));
	return res;
}
void dfs1(int u,int ff){
	in[u]=++dn;
	dep[u]=dep[ff]+1;
	for(int v:e[u])if(v!=ff)dfs1(v,u);
	out[u]=dn;
	if(u!=1)modify(1,1,n,in[u],out[u],1);
}
vector<pii> rg;
void dfs2(int u,int ff){
	for(int i:que[u]){
		rg.clear();
		for(int j:q[i]){
			if(in[j]<=in[u]&&in[u]<=out[j]){
				rg.pb(mk(1,in[nxt[j]]-1));
				rg.pb(mk(out[nxt[j]]+1,dn));
			}else rg.pb(mk(in[j],out[j]));
		}
		sort(rg.begin(),rg.end());
		int pre=1;
		for(pii j:rg){
			if(pre<j.fi)ans[i]=max(ans[i],query(1,1,dn,pre,j.fi-1));
			pre=max(pre,j.se+1);
		}
		if(pre<=dn)ans[i]=max(ans[i],query(1,1,dn,pre,dn));
	}
	tag(1,1);
	for(int v:e[u])if(v!=ff){
		nxt[u]=v;
		modify(1,1,dn,in[v],out[v],-2);
		dfs2(v,u);
		modify(1,1,dn,in[v],out[v],2);
	}tag(1,-1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;++i)scanf("%d%d",&u,&v),e[u].pb(v),e[v].pb(u);
	dfs1(1,0);
	for(int i=1,po,len;i<=m;++i){
		scanf("%d%d",&po,&len);
		for(int j=1,x;j<=len;++j)scanf("%d",&x),q[i].pb(x);
		que[po].pb(i);
	}
	dfs2(1,0);
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}