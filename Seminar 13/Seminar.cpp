/*SMB(S,b)
{
    slp[]=inf
    dp[0]=0
    for(i=1;i<b;i++)
    min[b]=
}
*/


Drumuri arbore :
dp=[];
dp1=[];
struct Node
{ 
 int val; 
 vector<Node*> chilldrem;
}
Dfs(root)
{
    if(root==Null)
    return;
    dp0[root->id]=0;
    dp[root->id]=root->val;
    for(child in root->children)
    {
        Dfs(child);
        dp1[root->id]+=dp0[child->id];
        dp0[root->id]+=max(dp0[child->id],dp1[child->id]);
    }
}
 SMax()
{
   Dfs(root);
   print(max(dp0[root->id],dp1[root->id])); 
}

