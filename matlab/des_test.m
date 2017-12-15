d='romantic';
k='12345678';
dhex=dec2hex(abs(d));
khex=dec2hex(abs(k));
e=reshape(DES(dhex,khex,1),8,2);
edec=hex2dec(e);
char(edec')

d2=reshape(DES(e,khex,0),8,2);
d2dec=hex2dec(d2);
char(d2dec')



