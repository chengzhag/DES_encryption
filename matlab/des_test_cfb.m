%% 参数设置
key='12345678';
m='Cipher feedback';

%% 常数
mLength=length(m);
mHexLength=ceil(mLength/8)*8;
mHex=char(zeros(mHexLength,2));
mHex(1:mLength,:)=dec2hex(abs(m));
k=dec2hex(abs(key));
iv=k;

%% 密文反馈（CFB）循环
d=iv;
blockBegin=1;
blockEnd=8;
for i=1:mHexLength/8
    c=DES(d,k,1);
    
    c=hex2dec(reshape(c,1,16));
    
    block=reshape(mHex(blockBegin:blockEnd,:),1,16);
    block=hex2dec(block);
    
    resultXor=bitxor(c,block,'uint64')
    
    blockBegin=blockBegin+8;
    blockEnd=blockBegin+8;
end


