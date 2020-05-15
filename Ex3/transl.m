
%first enter manually inNode and outNode with data from ping_pong.c

inNodeFit = polyfit(inNode(:,1), inNode(:,2),1);
outNodeFit = polyfit(outNode(:,1), outNode(:,2),1);

outS = outNodeFit(2)
outBwdth = 1 / outNodeFit(1)

inS = inNodeFit(2)
inBwdth = 1 / inNodeFit(1)


