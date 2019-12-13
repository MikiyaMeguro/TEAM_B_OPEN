xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 248;
 -2.01834;-0.92860;0.38511;,
 -2.13602;-0.00762;0.40965;,
 -2.15072;0.00296;-0.42037;,
 -2.03130;-0.91927;-0.34705;,
 -0.18171;-0.83798;0.31446;,
 -0.59690;-0.90382;0.34788;,
 -0.60935;-0.89483;-0.35750;,
 -0.19320;-0.82965;-0.33711;,
 -0.06549;-0.01980;0.33240;,
 -0.07849;-0.01037;-0.40628;,
 -0.58471;0.88578;0.37044;,
 -0.17044;0.81517;0.33532;,
 -0.18199;0.82346;-0.31625;,
 -0.59718;0.89476;-0.33492;,
 -0.64799;-0.82045;-0.82191;,
 -0.55030;0.00064;-1.02517;,
 -0.19637;-0.00436;-0.81951;,
 -0.29344;-0.73009;-0.73315;,
 -0.05529;-0.02712;0.90897;,
 -0.51362;-0.02582;1.05151;,
 -0.61873;-0.84150;0.83098;,
 -0.26758;-0.74878;0.73207;,
 -2.00570;0.92893;0.40855;,
 -2.01864;0.93825;-0.32361;,
 -0.63679;0.83267;-0.80106;,
 -0.28353;0.73530;-0.71465;,
 -0.25760;0.71665;0.75057;,
 -0.60755;0.81161;0.85185;,
 -1.53666;-1.00880;0.40580;,
 -1.55067;-0.99870;-0.38680;,
 -1.52474;-0.91561;-0.90986;,
 -1.63034;0.00843;-1.13443;,
 -1.51209;0.94193;-0.88643;,
 -1.52296;1.00204;0.43117;,
 -1.53703;1.01213;-0.36142;,
 -1.47928;0.91827;0.97086;,
 -1.58906;-0.02128;1.19903;,
 -1.49190;-0.93928;0.94741;,
 -2.03485;0.00808;-0.88909;,
 -1.93299;-0.80878;-0.79577;,
 -1.92187;0.83780;-0.77502;,
 -2.00570;0.92893;0.40855;,
 -2.01864;0.93825;-0.32361;,
 -1.89273;0.81685;0.87137;,
 -2.00199;-0.01558;0.96819;,
 -1.90390;-0.82976;0.85060;,
 -1.47928;0.91827;0.97086;,
 -1.89273;0.81685;0.87137;,
 -0.60755;0.81161;0.85185;,
 -0.25760;0.71665;0.75057;,
 -0.05529;-0.02712;0.90897;,
 -0.26758;-0.74878;0.73207;,
 -0.61873;-0.84150;0.83098;,
 -1.49190;-0.93928;0.94741;,
 -0.19637;-0.00436;-0.81951;,
 -0.28353;0.73530;-0.71465;,
 -0.63679;0.83267;-0.80106;,
 -1.51209;0.94193;-0.88643;,
 -1.92187;0.83780;-0.77502;,
 -1.52474;-0.91561;-0.90986;,
 -0.64799;-0.82045;-0.82191;,
 -0.29344;-0.73009;-0.73315;,
 -2.11247;-0.73292;1.76592;,
 -2.14549;-0.07926;1.85450;,
 -2.65703;-0.07207;1.55985;,
 -2.56371;-0.72659;1.50601;,
 -1.48409;-0.65007;0.62106;,
 -1.61529;-0.70104;0.88586;,
 -2.05004;-0.69494;0.63546;,
 -1.88569;-0.64443;0.38976;,
 -1.43505;-0.06716;0.56371;,
 -1.89031;-0.06076;0.30148;,
 -1.60662;0.57152;0.90193;,
 -1.47614;0.52546;0.63590;,
 -1.87770;0.53111;0.40458;,
 -2.04140;0.57762;0.65152;,
 -2.34777;-0.64254;0.48974;,
 -2.44034;-0.05779;0.36282;,
 -2.18541;-0.05775;0.22220;,
 -2.16442;-0.57472;0.30684;,
 -1.07974;-0.07217;0.76837;,
 -1.16047;-0.07579;1.10002;,
 -1.32908;-0.65687;1.07648;,
 -1.26139;-0.58742;0.82697;,
 -2.10346;0.58795;1.78259;,
 -2.55474;0.59430;1.52268;,
 -2.33976;0.53300;0.50457;,
 -2.15730;0.46733;0.32000;,
 -1.25430;0.45462;0.84010;,
 -1.32105;0.51866;1.09133;,
 -1.92324;-0.78514;1.47912;,
 -2.41170;-0.77827;1.19777;,
 -2.72157;-0.71902;0.99130;,
 -2.90208;-0.06310;0.98139;,
 -2.71262;0.60185;1.00797;,
 -1.91347;0.64478;1.49718;,
 -2.40194;0.65166;1.21583;,
 -1.56797;0.58575;1.66727;,
 -1.46399;-0.08335;1.80972;,
 -1.57696;-0.73512;1.65060;,
 -2.90046;-0.06737;1.31775;,
 -2.80199;-0.64715;1.28287;,
 -2.79403;0.52375;1.29765;,
 -2.10346;0.58795;1.78259;,
 -2.55474;0.59430;1.52268;,
 -1.77934;0.50948;1.88209;,
 -1.75584;-0.08346;1.97705;,
 -1.78730;-0.66143;1.86731;,
 -1.56797;0.58575;1.66727;,
 -1.77934;0.50948;1.88209;,
 -1.32105;0.51866;1.09133;,
 -1.25430;0.45462;0.84010;,
 -1.07974;-0.07217;0.76837;,
 -1.26139;-0.58742;0.82697;,
 -1.32908;-0.65687;1.07648;,
 -1.57696;-0.73512;1.65060;,
 -2.18541;-0.05775;0.22220;,
 -2.15730;0.46733;0.32000;,
 -2.33976;0.53300;0.50457;,
 -2.71262;0.60185;1.00797;,
 -2.79403;0.52375;1.29765;,
 -2.72157;-0.71902;0.99130;,
 -2.34777;-0.64254;0.48974;,
 -2.16442;-0.57472;0.30684;,
 -2.67097;-0.63511;-1.25174;,
 -2.73208;0.02049;-1.30314;,
 -2.29848;0.02260;-1.70380;,
 -2.28851;-0.63326;-1.60518;,
 -1.76338;-0.58048;-0.31057;,
 -1.97820;-0.62496;-0.51508;,
 -1.60976;-0.62317;-0.85557;,
 -1.42306;-0.57883;-0.62513;,
 -1.71108;0.00081;-0.24091;,
 -1.32525;0.00268;-0.59751;,
 -1.96958;0.64760;-0.49903;,
 -1.75539;0.59505;-0.29575;,
 -1.41508;0.59670;-0.61028;,
 -1.60114;0.64940;-0.83952;,
 -1.38098;-0.57317;-1.09594;,
 -1.22008;0.00883;-1.14084;,
 -1.16173;0.00483;-0.85563;,
 -1.25954;-0.51014;-0.86585;,
 -2.01231;-0.00067;0.03741;,
 -2.30485;0.00355;-0.13836;,
 -2.24440;-0.57738;-0.29804;,
 -2.02492;-0.51386;-0.15855;,
 -2.66198;0.68576;-1.23507;,
 -2.27953;0.68761;-1.58851;,
 -1.37299;0.60237;-1.08109;,
 -1.25243;0.53192;-0.85269;,
 -2.01783;0.52818;-0.14539;,
 -2.23642;0.59817;-0.28320;,
 -2.45459;-0.69448;-0.98627;,
 -2.04063;-0.69245;-1.36889;,
 -1.75008;-0.63694;-1.60278;,
 -1.67327;0.01913;-1.76569;,
 -1.74110;0.68393;-1.58611;,
 -2.44486;0.73545;-0.96824;,
 -2.03086;0.73745;-1.35085;,
 -2.71128;0.67919;-0.68954;,
 -2.89217;0.01318;-0.63924;,
 -2.72018;-0.64167;-0.70621;,
 -1.99487;0.02255;-1.86418;,
 -2.00299;-0.55818;-1.76551;,
 -1.99498;0.61271;-1.75072;,
 -2.66198;0.68576;-1.23507;,
 -2.27953;0.68761;-1.58851;,
 -2.85503;0.60855;-0.95596;,
 -2.96504;0.01785;-0.96760;,
 -2.86299;-0.56235;-0.97073;,
 -2.71128;0.67919;-0.68954;,
 -2.85503;0.60855;-0.95596;,
 -2.23642;0.59817;-0.28320;,
 -2.01783;0.52818;-0.14539;,
 -2.01231;-0.00067;0.03741;,
 -2.02492;-0.51386;-0.15855;,
 -2.24440;-0.57738;-0.29804;,
 -2.72018;-0.64167;-0.70621;,
 -1.16173;0.00483;-0.85563;,
 -1.25243;0.53192;-0.85269;,
 -1.37299;0.60237;-1.08109;,
 -1.74110;0.68393;-1.58611;,
 -1.99498;0.61271;-1.75072;,
 -1.75008;-0.63694;-1.60278;,
 -1.38098;-0.57317;-1.09594;,
 -1.25954;-0.51014;-0.86585;,
 -3.11718;-0.65172;0.30482;,
 -3.20090;0.00317;0.32229;,
 -3.21137;0.01067;-0.26794;,
 -3.12641;-0.64509;-0.21580;,
 -1.81117;-0.58728;0.25460;,
 -2.10641;-0.63410;0.27835;,
 -2.11526;-0.62772;-0.22323;,
 -1.81936;-0.58139;-0.20874;,
 -1.72855;-0.00550;0.26734;,
 -1.73781;0.00120;-0.25792;,
 -2.09774;0.63846;0.29441;,
 -1.80315;0.58824;0.26943;,
 -1.81135;0.59414;-0.19389;,
 -2.10663;0.64485;-0.20718;,
 -2.14278;-0.57485;-0.55348;,
 -2.07336;0.00903;-0.69800;,
 -1.82160;0.00548;-0.55176;,
 -1.89069;-0.51059;-0.49036;,
 -1.72128;-0.01071;0.67735;,
 -2.04722;-0.00977;0.77871;,
 -2.12195;-0.58981;0.62187;,
 -1.87227;-0.52387;0.55156;,
 -3.10820;0.66913;0.32150;,
 -3.11743;0.67577;-0.19913;,
 -2.13474;0.60070;-0.53865;,
 -1.88353;0.53146;-0.47721;,
 -1.86516;0.51817;0.56469;,
 -2.11398;0.58571;0.63673;,
 -2.77471;-0.70877;0.31953;,
 -2.78466;-0.70159;-0.24405;,
 -2.76620;-0.64250;-0.61601;,
 -2.84128;0.01458;-0.77569;,
 -2.75724;0.67838;-0.59935;,
 -2.76496;0.72114;0.33759;,
 -2.77499;0.72833;-0.22601;,
 -2.73384;0.66155;0.72136;,
 -2.81195;-0.00656;0.88361;,
 -2.74286;-0.65934;0.70469;,
 -3.12892;0.01433;-0.60123;,
 -3.05651;-0.56654;-0.53490;,
 -3.04859;0.60434;-0.52012;,
 -3.10820;0.66913;0.32150;,
 -3.11743;0.67577;-0.19913;,
 -3.02791;0.58943;0.65061;,
 -3.10555;-0.00249;0.71947;,
 -3.03586;-0.58145;0.63583;,
 -2.73384;0.66155;0.72136;,
 -3.02791;0.58943;0.65061;,
 -2.11398;0.58571;0.63673;,
 -1.86516;0.51817;0.56469;,
 -1.72128;-0.01071;0.67735;,
 -1.87227;-0.52387;0.55156;,
 -2.12195;-0.58981;0.62187;,
 -2.74286;-0.65934;0.70469;,
 -1.82160;0.00548;-0.55176;,
 -1.88353;0.53146;-0.47721;,
 -2.13474;0.60070;-0.53865;,
 -2.75724;0.67838;-0.59935;,
 -3.04859;0.60434;-0.52012;,
 -2.76620;-0.64250;-0.61601;,
 -2.14278;-0.57485;-0.55348;,
 -1.89069;-0.51059;-0.49036;;
 
 168;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;1,22,23,2;,
 4;15,24,25,16;,
 4;11,8,9,12;,
 4;26,27,19,18;,
 4;5,28,29,6;,
 4;30,31,15,14;,
 4;31,32,24,15;,
 4;33,10,13,34;,
 4;19,27,35,36;,
 4;20,19,36,37;,
 4;28,0,3,29;,
 4;38,31,30,39;,
 4;40,32,31,38;,
 4;41,33,34,42;,
 4;36,35,43,44;,
 4;37,36,44,45;,
 4;46,33,41,47;,
 4;48,10,33,46;,
 4;49,11,10,48;,
 4;50,8,11,49;,
 4;51,4,8,50;,
 4;52,5,4,51;,
 4;53,28,5,52;,
 4;45,0,28,53;,
 4;44,1,0,45;,
 4;43,22,1,44;,
 4;12,9,54,55;,
 4;13,12,55,56;,
 4;34,13,56,57;,
 4;42,34,57,58;,
 4;2,23,40,38;,
 4;3,2,38,39;,
 4;29,3,39,59;,
 4;6,29,59,60;,
 4;7,6,60,61;,
 4;9,7,61,54;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,66,69,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;63,84,85,64;,
 4;77,86,87,78;,
 4;73,70,71,74;,
 4;88,89,81,80;,
 4;67,90,91,68;,
 4;92,93,77,76;,
 4;93,94,86,77;,
 4;95,72,75,96;,
 4;81,89,97,98;,
 4;82,81,98,99;,
 4;90,62,65,91;,
 4;100,93,92,101;,
 4;102,94,93,100;,
 4;103,95,96,104;,
 4;98,97,105,106;,
 4;99,98,106,107;,
 4;108,95,103,109;,
 4;110,72,95,108;,
 4;111,73,72,110;,
 4;112,70,73,111;,
 4;113,66,70,112;,
 4;114,67,66,113;,
 4;115,90,67,114;,
 4;107,62,90,115;,
 4;106,63,62,107;,
 4;105,84,63,106;,
 4;74,71,116,117;,
 4;75,74,117,118;,
 4;96,75,118,119;,
 4;104,96,119,120;,
 4;64,85,102,100;,
 4;65,64,100,101;,
 4;91,65,101,121;,
 4;68,91,121,122;,
 4;69,68,122,123;,
 4;71,69,123,116;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,128,131,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;125,146,147,126;,
 4;139,148,149,140;,
 4;135,132,133,136;,
 4;150,151,143,142;,
 4;129,152,153,130;,
 4;154,155,139,138;,
 4;155,156,148,139;,
 4;157,134,137,158;,
 4;143,151,159,160;,
 4;144,143,160,161;,
 4;152,124,127,153;,
 4;162,155,154,163;,
 4;164,156,155,162;,
 4;165,157,158,166;,
 4;160,159,167,168;,
 4;161,160,168,169;,
 4;170,157,165,171;,
 4;172,134,157,170;,
 4;173,135,134,172;,
 4;174,132,135,173;,
 4;175,128,132,174;,
 4;176,129,128,175;,
 4;177,152,129,176;,
 4;169,124,152,177;,
 4;168,125,124,169;,
 4;167,146,125,168;,
 4;136,133,178,179;,
 4;137,136,179,180;,
 4;158,137,180,181;,
 4;166,158,181,182;,
 4;126,147,164,162;,
 4;127,126,162,163;,
 4;153,127,163,183;,
 4;130,153,183,184;,
 4;131,130,184,185;,
 4;133,131,185,178;,
 4;186,187,188,189;,
 4;190,191,192,193;,
 4;194,190,193,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;187,208,209,188;,
 4;201,210,211,202;,
 4;197,194,195,198;,
 4;212,213,205,204;,
 4;191,214,215,192;,
 4;216,217,201,200;,
 4;217,218,210,201;,
 4;219,196,199,220;,
 4;205,213,221,222;,
 4;206,205,222,223;,
 4;214,186,189,215;,
 4;224,217,216,225;,
 4;226,218,217,224;,
 4;227,219,220,228;,
 4;222,221,229,230;,
 4;223,222,230,231;,
 4;232,219,227,233;,
 4;234,196,219,232;,
 4;235,197,196,234;,
 4;236,194,197,235;,
 4;237,190,194,236;,
 4;238,191,190,237;,
 4;239,214,191,238;,
 4;231,186,214,239;,
 4;230,187,186,231;,
 4;229,208,187,230;,
 4;198,195,240,241;,
 4;199,198,241,242;,
 4;220,199,242,243;,
 4;228,220,243,244;,
 4;188,209,226,224;,
 4;189,188,224,225;,
 4;215,189,225,245;,
 4;192,215,245,246;,
 4;193,192,246,247;,
 4;195,193,247,240;;
 
 MeshMaterialList {
  1;
  168;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\dog_color.jpg";
   }
  }
 }
 MeshNormals {
  272;
  -0.745364;0.196995;0.636887;,
  -0.757410;0.218176;-0.615410;,
  -0.747727;-0.206517;0.631075;,
  -0.759754;-0.196065;-0.619945;,
  0.307062;-0.716636;0.626216;,
  0.739220;-0.205583;-0.641319;,
  0.632879;0.580966;0.511803;,
  0.742435;0.207918;-0.636836;,
  -0.762224;-0.004896;0.647295;,
  -0.775399;0.011260;-0.631371;,
  0.757190;0.001159;-0.653194;,
  0.320173;-0.016752;0.947211;,
  0.224819;-0.279075;0.933581;,
  0.255955;-0.228651;-0.939258;,
  0.264951;0.008228;-0.964227;,
  0.258894;0.244641;-0.934411;,
  0.228159;0.247704;0.941587;,
  0.234782;-0.016259;0.971912;,
  -0.127562;-0.255933;0.958241;,
  -0.161471;-0.231529;-0.959334;,
  -0.164763;0.011355;-0.986268;,
  -0.158215;0.253541;-0.954298;,
  -0.124292;0.229085;0.965438;,
  -0.129803;-0.013828;0.991443;,
  -0.980686;0.141461;0.135067;,
  -0.027175;0.994598;0.100186;,
  0.168606;0.981027;0.095698;,
  0.207260;0.971925;0.111379;,
  0.998917;-0.008942;0.045673;,
  0.194042;-0.977147;0.086787;,
  0.155254;-0.985328;0.070890;,
  -0.040710;-0.996346;0.075076;,
  -0.982188;-0.134025;0.131698;,
  -0.990884;0.003755;0.134667;,
  0.988878;-0.006185;-0.148602;,
  0.203991;0.974092;-0.097633;,
  0.165837;0.982932;-0.079647;,
  -0.030374;0.996577;-0.076890;,
  -0.982374;0.150926;-0.110284;,
  -0.993530;0.006834;-0.113366;,
  -0.983924;-0.137404;-0.114078;,
  -0.043903;-0.993814;-0.102015;,
  0.152486;-0.982770;-0.104455;,
  0.190779;-0.973995;-0.122216;,
  0.161188;0.186658;0.969112;,
  -0.919016;0.207250;0.335347;,
  0.158002;-0.216877;0.963327;,
  -0.920994;-0.206912;0.330087;,
  0.700316;-0.712054;0.050367;,
  -0.168080;-0.195322;-0.966229;,
  0.760075;0.589983;-0.272408;,
  -0.165682;0.218161;-0.961746;,
  0.162947;-0.015462;0.986514;,
  -0.940393;0.000137;0.340090;,
  -0.170567;0.011636;-0.985277;,
  0.977073;-0.011965;0.212570;,
  0.918281;-0.275632;0.284231;,
  -0.672020;-0.225276;-0.705436;,
  -0.690578;0.011683;-0.723164;,
  -0.669904;0.247978;-0.699811;,
  0.922924;0.251185;0.291750;,
  0.954314;-0.012671;0.298536;,
  0.757963;-0.257451;0.599342;,
  -0.903940;-0.234029;-0.357943;,
  -0.930552;0.008742;-0.366055;,
  -0.901604;0.250975;-0.352310;,
  0.762166;0.227602;0.606052;,
  0.783462;-0.015374;0.621250;,
  -0.389751;0.127656;0.912030;,
  0.064474;0.994142;0.086744;,
  0.161441;0.983335;-0.083600;,
  0.194839;0.974784;-0.108787;,
  0.553125;0.005183;-0.833082;,
  0.181597;-0.974288;-0.133360;,
  0.148080;-0.983016;-0.108405;,
  0.050924;-0.996799;0.061630;,
  -0.391370;-0.147860;0.908277;,
  -0.394321;-0.010198;0.918916;,
  0.381343;0.007717;-0.924401;,
  0.013912;0.976851;-0.213469;,
  0.009632;0.985152;-0.171411;,
  -0.089052;0.996026;-0.001619;,
  -0.601114;0.137000;0.787333;,
  -0.608390;-0.007226;0.793605;,
  -0.602956;-0.151303;0.783296;,
  -0.102591;-0.994365;-0.026725;,
  -0.003732;-0.980550;-0.196235;,
  0.000669;-0.971245;-0.238080;,
  -0.969067;0.208259;-0.132425;,
  -0.042334;0.217847;-0.975064;,
  -0.971018;-0.195359;-0.137690;,
  -0.045416;-0.196341;-0.979483;,
  -0.271298;-0.712969;0.646585;,
  0.968184;-0.216808;0.124954;,
  0.046108;0.581156;0.812485;,
  0.971824;0.196623;0.129992;,
  -0.990425;0.006553;-0.137896;,
  -0.044848;0.010956;-0.998934;,
  0.991422;-0.010356;0.130287;,
  -0.493934;-0.010242;0.869439;,
  -0.550292;-0.272004;0.789426;,
  0.868584;-0.239175;-0.434002;,
  0.895958;-0.002631;-0.444130;,
  0.872438;0.234062;-0.429030;,
  -0.547862;0.254794;0.796823;,
  -0.569181;-0.008919;0.822164;,
  -0.802916;-0.246161;0.542891;,
  0.605672;-0.239241;-0.758897;,
  0.626405;0.003380;-0.779491;,
  0.609732;0.245782;-0.753537;,
  -0.800468;0.238940;0.549689;,
  -0.826374;-0.003714;0.563109;,
  -0.751908;0.149738;-0.642039;,
  -0.081220;0.995654;0.045574;,
  0.052291;0.980642;0.188698;,
  0.066227;0.971409;0.227989;,
  0.630709;-0.015646;0.775861;,
  0.052966;-0.977665;0.203387;,
  0.038925;-0.985713;0.163877;,
  -0.094761;-0.995290;0.020450;,
  -0.753597;-0.125806;-0.645185;,
  -0.760001;0.012082;-0.649809;,
  0.769044;-0.014648;0.639028;,
  0.219980;0.971667;0.086440;,
  0.181289;0.980941;0.069919;,
  0.048811;0.996010;-0.074708;,
  -0.569759;0.156918;-0.806691;,
  -0.576600;0.012886;-0.816925;,
  -0.571392;-0.131417;-0.810087;,
  0.035285;-0.994381;-0.099809;,
  0.167935;-0.984766;0.045095;,
  0.206758;-0.976437;0.061828;,
  -0.745362;0.196995;0.636889;,
  -0.757372;0.218168;-0.615459;,
  -0.747743;-0.206509;0.631059;,
  -0.759722;-0.196053;-0.619989;,
  0.307057;-0.716653;0.626198;,
  0.739186;-0.205609;-0.641349;,
  0.632904;0.580935;0.511808;,
  0.742452;0.207837;-0.636843;,
  -0.762230;-0.004893;0.647287;,
  -0.775361;0.011265;-0.631417;,
  0.757177;0.001098;-0.653209;,
  0.320189;-0.016746;0.947206;,
  0.224812;-0.279083;0.933580;,
  0.255925;-0.228641;-0.939269;,
  0.264904;0.008211;-0.964240;,
  0.258836;0.244597;-0.934439;,
  0.228187;0.247713;0.941578;,
  0.234793;-0.016259;0.971909;,
  -0.127564;-0.255936;0.958240;,
  -0.161454;-0.231499;-0.959344;,
  -0.164759;0.011362;-0.986268;,
  -0.158226;0.253526;-0.954300;,
  -0.124282;0.229085;0.965440;,
  -0.129798;-0.013828;0.991444;,
  -0.980683;0.141471;0.135083;,
  -0.027194;0.994594;0.100215;,
  0.168631;0.981020;0.095722;,
  0.207301;0.971913;0.111406;,
  0.998916;-0.008958;0.045679;,
  0.194041;-0.977148;0.086779;,
  0.155256;-0.985328;0.070878;,
  -0.040729;-0.996347;0.075061;,
  -0.982185;-0.134049;0.131697;,
  -0.990883;0.003748;0.134674;,
  0.988880;-0.006232;-0.148588;,
  0.203991;0.974095;-0.097603;,
  0.165838;0.982932;-0.079638;,
  -0.030408;0.996575;-0.076906;,
  -0.982365;0.150951;-0.110327;,
  -0.993526;0.006826;-0.113397;,
  -0.983916;-0.137444;-0.114096;,
  -0.043922;-0.993814;-0.102003;,
  0.152485;-0.982772;-0.104440;,
  0.190770;-0.973998;-0.122203;,
  0.983367;-0.176468;0.042984;,
  0.977366;-0.150287;-0.148897;,
  0.986183;0.158831;0.047068;,
  0.979725;0.138044;-0.145202;,
  -0.197267;-0.975890;0.093408;,
  -0.201345;-0.972754;-0.114932;,
  -0.184001;0.975815;0.118018;,
  -0.188094;0.977991;-0.090305;,
  -0.040702;0.981476;0.187210;,
  -0.215394;0.951565;0.219383;,
  0.189660;0.965062;0.180789;,
  0.993918;-0.010093;0.109657;,
  0.971657;-0.211807;0.104975;,
  0.176511;-0.971801;0.156353;,
  -0.054082;-0.985239;0.162415;,
  -0.228364;-0.953770;0.195378;,
  0.236548;0.950055;-0.203569;,
  0.184047;0.968316;-0.168792;,
  -0.047082;0.984877;-0.166736;,
  -0.223376;0.955085;-0.194721;,
  -0.236307;-0.946738;-0.218737;,
  -0.060442;-0.979621;-0.191546;,
  0.170910;-0.966156;-0.193216;,
  0.223683;-0.947735;-0.227519;,
  0.544079;-0.162552;-0.823137;,
  0.376228;-0.136523;-0.916414;,
  0.546510;0.172765;-0.819438;,
  0.378490;0.151793;-0.913074;,
  -0.014074;-0.978544;0.205557;,
  -0.194824;-0.975531;0.101893;,
  -0.000771;0.973152;0.230162;,
  -0.181552;0.975213;0.126482;,
  0.132250;0.980851;0.142974;,
  0.070205;0.948484;0.308949;,
  0.245368;0.967689;-0.058067;,
  0.605454;0.003989;-0.795870;,
  0.591526;-0.198044;-0.781585;,
  0.232192;-0.969165;-0.082497;,
  0.118845;-0.985859;0.118144;,
  0.057192;-0.956849;0.284903;,
  -0.059980;0.953247;-0.296179;,
  -0.057332;0.970770;-0.233063;,
  -0.174610;0.984062;-0.033666;,
  -0.289066;0.951783;0.102716;,
  -0.302005;-0.950051;0.078719;,
  -0.187985;-0.980430;-0.058468;,
  -0.070508;-0.963698;-0.257515;,
  -0.072905;-0.944547;-0.320181;,
  0.620410;-0.183094;0.762606;,
  0.759941;-0.158647;0.630334;,
  0.623147;0.152240;0.767145;,
  0.762078;0.129653;0.634371;,
  -0.212416;-0.973546;-0.084191;,
  -0.059627;-0.972321;-0.225912;,
  -0.199122;0.978162;-0.059572;,
  -0.046379;0.978424;-0.201333;,
  -0.155324;0.983435;0.093433;,
  -0.295942;0.955081;-0.015474;,
  0.002619;0.965317;0.261067;,
  0.579535;-0.016162;0.814787;,
  0.565843;-0.217779;0.795232;,
  -0.010530;-0.971545;0.236622;,
  -0.168701;-0.983276;0.068613;,
  -0.308926;-0.950265;-0.039507;,
  0.320374;0.946435;0.040271;,
  0.259733;0.965378;0.024192;,
  0.104587;0.983595;-0.146978;,
  0.007772;0.954799;-0.297152;,
  -0.005110;-0.947036;-0.321086;,
  0.091249;-0.980907;-0.171739;,
  0.246615;-0.969113;-0.000244;,
  0.307549;-0.951393;0.016282;,
  0.983369;-0.176458;0.042986;,
  0.977359;-0.150296;-0.148929;,
  0.986189;0.158789;0.047079;,
  0.979745;0.137959;-0.145144;,
  -0.197310;-0.975883;0.093393;,
  -0.201388;-0.972746;-0.114925;,
  -0.184045;0.975803;0.118052;,
  -0.188164;0.977975;-0.090324;,
  -0.040706;0.981467;0.187257;,
  -0.215404;0.951552;0.219431;,
  0.189693;0.965047;0.180836;,
  0.993914;-0.010104;0.109694;,
  0.971652;-0.211814;0.105013;,
  0.176518;-0.971807;0.156307;,
  -0.054093;-0.985245;0.162377;,
  -0.228385;-0.953772;0.195346;,
  0.236533;0.950071;-0.203512;,
  0.184035;0.968321;-0.168775;,
  -0.047117;0.984868;-0.166777;,
  -0.223436;0.955060;-0.194776;,
  -0.236327;-0.946736;-0.218726;,
  -0.060454;-0.979623;-0.191530;,
  0.170908;-0.966158;-0.193208;,
  0.223680;-0.947734;-0.227525;;
  168;
  4;32,33,39,40;,
  4;29,30,42,43;,
  4;28,176,177,34;,
  4;26,27,35,36;,
  4;13,14,10,5;,
  4;11,17,12,4;,
  4;33,24,38,39;,
  4;14,15,7,10;,
  4;178,28,34,179;,
  4;6,16,17,11;,
  4;30,31,41,42;,
  4;19,20,14,13;,
  4;20,21,15,14;,
  4;25,26,36,37;,
  4;17,16,22,23;,
  4;12,17,23,18;,
  4;31,180,181,41;,
  4;9,20,19,3;,
  4;1,21,20,9;,
  4;182,25,37,183;,
  4;23,22,0,8;,
  4;18,23,8,2;,
  4;184,25,182,185;,
  4;186,26,25,184;,
  4;6,27,26,186;,
  4;187,28,178,6;,
  4;188,176,28,187;,
  4;189,30,29,4;,
  4;190,31,30,189;,
  4;191,180,31,190;,
  4;8,33,32,2;,
  4;0,24,33,8;,
  4;179,34,10,7;,
  4;36,35,192,193;,
  4;37,36,193,194;,
  4;183,37,194,195;,
  4;39,38,1,9;,
  4;40,39,9,3;,
  4;41,181,196,197;,
  4;42,41,197,198;,
  4;43,42,198,199;,
  4;34,177,5,10;,
  4;76,77,83,84;,
  4;73,74,86,87;,
  4;72,200,201,78;,
  4;70,71,79,80;,
  4;57,58,54,49;,
  4;55,61,56,48;,
  4;77,68,82,83;,
  4;58,59,51,54;,
  4;202,72,78,203;,
  4;50,60,61,55;,
  4;74,75,85,86;,
  4;63,64,58,57;,
  4;64,65,59,58;,
  4;69,70,80,81;,
  4;61,60,66,67;,
  4;56,61,67,62;,
  4;75,204,205,85;,
  4;53,64,63,47;,
  4;45,65,64,53;,
  4;206,69,81,207;,
  4;67,66,44,52;,
  4;62,67,52,46;,
  4;208,69,206,209;,
  4;210,70,69,208;,
  4;50,71,70,210;,
  4;211,72,202,50;,
  4;212,200,72,211;,
  4;213,74,73,48;,
  4;214,75,74,213;,
  4;215,204,75,214;,
  4;52,77,76,46;,
  4;44,68,77,52;,
  4;203,78,54,51;,
  4;80,79,216,217;,
  4;81,80,217,218;,
  4;207,81,218,219;,
  4;83,82,45,53;,
  4;84,83,53,47;,
  4;85,205,220,221;,
  4;86,85,221,222;,
  4;87,86,222,223;,
  4;78,201,49,54;,
  4;120,121,127,128;,
  4;117,118,130,131;,
  4;116,224,225,122;,
  4;114,115,123,124;,
  4;101,102,98,93;,
  4;99,105,100,92;,
  4;121,112,126,127;,
  4;102,103,95,98;,
  4;226,116,122,227;,
  4;94,104,105,99;,
  4;118,119,129,130;,
  4;107,108,102,101;,
  4;108,109,103,102;,
  4;113,114,124,125;,
  4;105,104,110,111;,
  4;100,105,111,106;,
  4;119,228,229,129;,
  4;97,108,107,91;,
  4;89,109,108,97;,
  4;230,113,125,231;,
  4;111,110,88,96;,
  4;106,111,96,90;,
  4;232,113,230,233;,
  4;234,114,113,232;,
  4;94,115,114,234;,
  4;235,116,226,94;,
  4;236,224,116,235;,
  4;237,118,117,92;,
  4;238,119,118,237;,
  4;239,228,119,238;,
  4;96,121,120,90;,
  4;88,112,121,96;,
  4;227,122,98,95;,
  4;124,123,240,241;,
  4;125,124,241,242;,
  4;231,125,242,243;,
  4;127,126,89,97;,
  4;128,127,97,91;,
  4;129,229,244,245;,
  4;130,129,245,246;,
  4;131,130,246,247;,
  4;122,225,93,98;,
  4;164,165,171,172;,
  4;161,162,174,175;,
  4;160,248,249,166;,
  4;158,159,167,168;,
  4;145,146,142,137;,
  4;143,149,144,136;,
  4;165,156,170,171;,
  4;146,147,139,142;,
  4;250,160,166,251;,
  4;138,148,149,143;,
  4;162,163,173,174;,
  4;151,152,146,145;,
  4;152,153,147,146;,
  4;157,158,168,169;,
  4;149,148,154,155;,
  4;144,149,155,150;,
  4;163,252,253,173;,
  4;141,152,151,135;,
  4;133,153,152,141;,
  4;254,157,169,255;,
  4;155,154,132,140;,
  4;150,155,140,134;,
  4;256,157,254,257;,
  4;258,158,157,256;,
  4;138,159,158,258;,
  4;259,160,250,138;,
  4;260,248,160,259;,
  4;261,162,161,136;,
  4;262,163,162,261;,
  4;263,252,163,262;,
  4;140,165,164,134;,
  4;132,156,165,140;,
  4;251,166,142,139;,
  4;168,167,264,265;,
  4;169,168,265,266;,
  4;255,169,266,267;,
  4;171,170,133,141;,
  4;172,171,141,135;,
  4;173,253,268,269;,
  4;174,173,269,270;,
  4;175,174,270,271;,
  4;166,249,137,142;;
 }
 MeshTextureCoords {
  248;
  0.500385;0.115523;,
  0.500385;0.126980;,
  0.507591;0.126980;,
  0.507591;0.115523;,
  0.500385;0.092398;,
  0.500385;0.097888;,
  0.507591;0.097888;,
  0.507591;0.092398;,
  0.500385;0.080941;,
  0.507591;0.080941;,
  0.500385;0.063784;,
  0.500385;0.069274;,
  0.507591;0.069274;,
  0.507591;0.063784;,
  0.529197;0.115523;,
  0.529197;0.126980;,
  0.534687;0.126980;,
  0.534687;0.115523;,
  0.465313;0.126980;,
  0.470803;0.126980;,
  0.470803;0.115523;,
  0.465313;0.115523;,
  0.500385;0.138647;,
  0.507591;0.138647;,
  0.529197;0.138647;,
  0.534687;0.138647;,
  0.465313;0.138647;,
  0.470803;0.138647;,
  0.500385;0.109095;,
  0.507591;0.109095;,
  0.517991;0.115523;,
  0.517991;0.126980;,
  0.517991;0.138647;,
  0.500385;0.052577;,
  0.507591;0.052577;,
  0.482009;0.138647;,
  0.482009;0.126980;,
  0.482009;0.115523;,
  0.511562;0.126980;,
  0.511562;0.115523;,
  0.511562;0.138647;,
  0.500385;0.046149;,
  0.507591;0.046149;,
  0.488438;0.138647;,
  0.488438;0.126980;,
  0.488438;0.115523;,
  0.488438;0.052577;,
  0.488438;0.046149;,
  0.488438;0.063784;,
  0.488438;0.069274;,
  0.488438;0.080941;,
  0.488438;0.092398;,
  0.488438;0.097888;,
  0.488438;0.109095;,
  0.511562;0.080941;,
  0.511562;0.069274;,
  0.511562;0.063784;,
  0.511562;0.052577;,
  0.511562;0.046149;,
  0.511562;0.109095;,
  0.511562;0.097888;,
  0.511562;0.092398;,
  0.500385;0.115523;,
  0.500385;0.126980;,
  0.507591;0.126980;,
  0.507591;0.115523;,
  0.500385;0.092398;,
  0.500385;0.097888;,
  0.507591;0.097888;,
  0.507591;0.092398;,
  0.500385;0.080941;,
  0.507591;0.080941;,
  0.500385;0.063784;,
  0.500385;0.069274;,
  0.507591;0.069274;,
  0.507591;0.063784;,
  0.529197;0.115523;,
  0.529197;0.126980;,
  0.534687;0.126980;,
  0.534687;0.115523;,
  0.465313;0.126980;,
  0.470803;0.126980;,
  0.470803;0.115523;,
  0.465313;0.115523;,
  0.500385;0.138647;,
  0.507591;0.138647;,
  0.529197;0.138647;,
  0.534687;0.138647;,
  0.465313;0.138647;,
  0.470803;0.138647;,
  0.500385;0.109095;,
  0.507591;0.109095;,
  0.517991;0.115523;,
  0.517991;0.126980;,
  0.517991;0.138647;,
  0.500385;0.052577;,
  0.507591;0.052577;,
  0.482009;0.138647;,
  0.482009;0.126980;,
  0.482009;0.115523;,
  0.511562;0.126980;,
  0.511562;0.115523;,
  0.511562;0.138647;,
  0.500385;0.046149;,
  0.507591;0.046149;,
  0.488438;0.138647;,
  0.488438;0.126980;,
  0.488438;0.115523;,
  0.488438;0.052577;,
  0.488438;0.046149;,
  0.488438;0.063784;,
  0.488438;0.069274;,
  0.488438;0.080941;,
  0.488438;0.092398;,
  0.488438;0.097888;,
  0.488438;0.109095;,
  0.511562;0.080941;,
  0.511562;0.069274;,
  0.511562;0.063784;,
  0.511562;0.052577;,
  0.511562;0.046149;,
  0.511562;0.109095;,
  0.511562;0.097888;,
  0.511562;0.092398;,
  0.500385;0.115523;,
  0.500385;0.126980;,
  0.507591;0.126980;,
  0.507591;0.115523;,
  0.500385;0.092398;,
  0.500385;0.097888;,
  0.507591;0.097888;,
  0.507591;0.092398;,
  0.500385;0.080941;,
  0.507591;0.080941;,
  0.500385;0.063784;,
  0.500385;0.069274;,
  0.507591;0.069274;,
  0.507591;0.063784;,
  0.529197;0.115523;,
  0.529197;0.126980;,
  0.534687;0.126980;,
  0.534687;0.115523;,
  0.465313;0.126980;,
  0.470803;0.126980;,
  0.470803;0.115523;,
  0.465313;0.115523;,
  0.500385;0.138647;,
  0.507591;0.138647;,
  0.529197;0.138647;,
  0.534687;0.138647;,
  0.465313;0.138647;,
  0.470803;0.138647;,
  0.500385;0.109095;,
  0.507591;0.109095;,
  0.517991;0.115523;,
  0.517991;0.126980;,
  0.517991;0.138647;,
  0.500385;0.052577;,
  0.507591;0.052577;,
  0.482009;0.138647;,
  0.482009;0.126980;,
  0.482009;0.115523;,
  0.511562;0.126980;,
  0.511562;0.115523;,
  0.511562;0.138647;,
  0.500385;0.046149;,
  0.507591;0.046149;,
  0.488438;0.138647;,
  0.488438;0.126980;,
  0.488438;0.115523;,
  0.488438;0.052577;,
  0.488438;0.046149;,
  0.488438;0.063784;,
  0.488438;0.069274;,
  0.488438;0.080941;,
  0.488438;0.092398;,
  0.488438;0.097888;,
  0.488438;0.109095;,
  0.511562;0.080941;,
  0.511562;0.069274;,
  0.511562;0.063784;,
  0.511562;0.052577;,
  0.511562;0.046149;,
  0.511562;0.109095;,
  0.511562;0.097888;,
  0.511562;0.092398;,
  0.500385;0.115523;,
  0.500385;0.126980;,
  0.507591;0.126980;,
  0.507591;0.115523;,
  0.500385;0.092398;,
  0.500385;0.097888;,
  0.507591;0.097888;,
  0.507591;0.092398;,
  0.500385;0.080941;,
  0.507591;0.080941;,
  0.500385;0.063784;,
  0.500385;0.069274;,
  0.507591;0.069274;,
  0.507591;0.063784;,
  0.529197;0.115523;,
  0.529197;0.126980;,
  0.534687;0.126980;,
  0.534687;0.115523;,
  0.465313;0.126980;,
  0.470803;0.126980;,
  0.470803;0.115523;,
  0.465313;0.115523;,
  0.500385;0.138647;,
  0.507591;0.138647;,
  0.529197;0.138647;,
  0.534687;0.138647;,
  0.465313;0.138647;,
  0.470803;0.138647;,
  0.500385;0.109095;,
  0.507591;0.109095;,
  0.517991;0.115523;,
  0.517991;0.126980;,
  0.517991;0.138647;,
  0.500385;0.052577;,
  0.507591;0.052577;,
  0.482009;0.138647;,
  0.482009;0.126980;,
  0.482009;0.115523;,
  0.511562;0.126980;,
  0.511562;0.115523;,
  0.511562;0.138647;,
  0.500385;0.046149;,
  0.507591;0.046149;,
  0.488438;0.138647;,
  0.488438;0.126980;,
  0.488438;0.115523;,
  0.488438;0.052577;,
  0.488438;0.046149;,
  0.488438;0.063784;,
  0.488438;0.069274;,
  0.488438;0.080941;,
  0.488438;0.092398;,
  0.488438;0.097888;,
  0.488438;0.109095;,
  0.511562;0.080941;,
  0.511562;0.069274;,
  0.511562;0.063784;,
  0.511562;0.052577;,
  0.511562;0.046149;,
  0.511562;0.109095;,
  0.511562;0.097888;,
  0.511562;0.092398;;
 }
}
