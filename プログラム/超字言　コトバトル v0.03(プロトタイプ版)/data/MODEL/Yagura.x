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
 288;
 8.16182;16.86278;10.30553;,
 0.89557;16.86278;10.30553;,
 0.89557;23.65393;10.30553;,
 8.16182;23.65393;10.30553;,
 0.89557;23.65393;12.74882;,
 8.16182;23.65393;12.74882;,
 0.89557;16.86278;12.74882;,
 8.16182;16.86278;12.74882;,
 0.89557;16.86278;10.30553;,
 8.16182;16.86278;10.30553;,
 0.89557;16.86278;12.74882;,
 0.89557;23.65393;12.74882;,
 8.16182;16.86278;12.74882;,
 8.16182;23.65393;12.74882;,
 12.70108;12.93552;-11.38217;,
 -11.23888;12.93552;-11.38217;,
 -11.23888;14.20892;-11.38217;,
 12.70108;14.20892;-11.38217;,
 -11.23888;14.20892;11.38217;,
 12.70108;14.20892;11.38217;,
 -11.23888;12.93552;11.38217;,
 12.70108;12.93552;11.38217;,
 -11.23888;12.93552;-11.38217;,
 12.70108;12.93552;-11.38217;,
 -11.23888;12.93552;11.38217;,
 -11.23888;14.20892;11.38217;,
 12.70108;12.93552;11.38217;,
 12.70108;14.20892;11.38217;,
 9.99377;16.82159;11.24469;,
 7.16823;16.82128;11.24469;,
 7.16823;23.06072;11.24469;,
 9.99377;23.06107;11.24469;,
 12.01761;16.82179;-0.71183;,
 7.16823;16.82128;-0.71183;,
 7.16823;23.06072;-0.71183;,
 12.01760;23.06001;-0.71183;,
 7.16823;23.06072;12.72856;,
 12.01760;23.06001;12.72856;,
 7.16823;16.82128;12.72856;,
 12.01761;16.82179;12.72856;,
 7.16823;16.82128;-0.71183;,
 12.01761;16.82179;-0.71183;,
 7.16823;16.82128;12.72856;,
 7.16823;23.06072;12.72856;,
 12.01761;16.82179;12.72856;,
 12.01760;23.06001;12.72856;,
 2.50017;16.82204;-0.71183;,
 -12.07555;16.82178;-0.71183;,
 -12.07555;23.06123;-0.71183;,
 2.50017;23.06152;-0.71183;,
 -12.07555;23.06123;12.72856;,
 2.50017;23.06152;12.72856;,
 -12.07555;16.82178;12.72856;,
 2.50017;16.82204;12.72856;,
 -12.07555;16.82178;-0.71183;,
 2.50017;16.82204;-0.71183;,
 -12.07555;16.82178;12.72856;,
 -12.07555;23.06123;12.72856;,
 2.50017;16.82204;12.72856;,
 2.50017;23.06152;12.72856;,
 12.01761;16.82179;-12.70742;,
 -12.07555;16.82178;-12.70742;,
 -12.07555;23.06123;-12.70742;,
 12.01761;23.06001;-12.70742;,
 -12.07555;23.06123;2.80909;,
 12.01761;23.06001;2.80909;,
 -12.07555;16.82178;2.80909;,
 12.01761;16.82179;2.80909;,
 -12.07555;16.82178;-12.70742;,
 12.01761;16.82179;-12.70742;,
 -12.07555;16.82178;2.80909;,
 -12.07555;23.06123;2.80909;,
 12.01761;16.82179;2.80909;,
 12.01761;23.06001;2.80909;,
 12.02220;22.98247;-12.76064;,
 -12.03451;22.98247;-12.76064;,
 -12.03451;32.98247;-12.76064;,
 12.02220;32.98247;-12.76064;,
 -12.03451;22.98247;-12.76064;,
 -12.03451;22.98247;12.78472;,
 -12.03451;32.98247;12.78472;,
 -12.03451;32.98247;-12.76064;,
 -12.03451;22.98247;12.78472;,
 12.02220;22.98247;12.78471;,
 12.02220;32.98247;12.78471;,
 -12.03451;32.98247;12.78472;,
 12.00292;22.98247;12.78472;,
 12.00292;22.98247;-12.76065;,
 12.00292;32.98247;-12.76065;,
 12.00292;32.98247;12.78472;,
 6.72193;1.96830;9.99692;,
 7.05431;1.96830;10.64925;,
 7.05431;37.68902;10.64925;,
 6.72193;37.68902;9.99692;,
 8.22433;1.96830;11.49932;,
 8.22433;37.68902;11.49932;,
 10.32289;1.96830;11.16694;,
 10.32289;37.68902;11.16694;,
 11.17296;1.96830;9.99692;,
 11.17296;37.68902;9.99692;,
 11.17296;1.96830;8.55069;,
 11.17296;37.68902;8.55069;,
 9.67056;1.96830;7.04829;,
 9.67056;37.68902;7.04829;,
 8.94744;1.96830;6.93376;,
 8.94744;37.68902;6.93376;,
 7.05431;1.96830;7.89836;,
 7.05431;37.68902;7.89836;,
 6.72193;1.96830;8.55069;,
 6.72193;37.68902;8.55069;,
 6.72193;1.96830;9.99692;,
 6.72193;37.68902;9.99692;,
 7.05431;1.96830;10.64925;,
 6.72193;1.96830;9.99692;,
 7.05431;1.96830;7.89836;,
 8.22433;1.96830;11.49932;,
 10.32289;1.96830;11.16694;,
 11.17296;1.96830;9.99692;,
 11.17296;1.96830;8.55069;,
 9.67056;1.96830;7.04829;,
 8.94744;1.96830;6.93376;,
 6.72193;1.96830;8.55069;,
 6.72193;37.68902;9.99692;,
 7.05431;37.68902;10.64925;,
 7.05431;37.68902;7.89836;,
 8.22433;37.68902;11.49932;,
 10.32289;37.68902;11.16694;,
 11.17296;37.68902;9.99692;,
 11.17296;37.68902;8.55069;,
 9.67056;37.68902;7.04829;,
 8.94744;37.68902;6.93376;,
 6.72193;37.68902;8.55069;,
 -10.50576;1.96830;9.99692;,
 -10.17339;1.96830;10.64925;,
 -10.17339;37.68902;10.64925;,
 -10.50576;37.68902;9.99692;,
 -9.00337;1.96830;11.49932;,
 -9.00337;37.68902;11.49932;,
 -6.90481;1.96830;11.16694;,
 -6.90481;37.68902;11.16694;,
 -6.05474;1.96830;9.99692;,
 -6.05474;37.68902;9.99692;,
 -6.05474;1.96830;8.55069;,
 -6.05474;37.68902;8.55069;,
 -7.55714;1.96830;7.04829;,
 -7.55714;37.68902;7.04829;,
 -8.28025;1.96830;6.93376;,
 -8.28025;37.68902;6.93376;,
 -10.17339;1.96830;7.89836;,
 -10.17339;37.68902;7.89836;,
 -10.50576;1.96830;8.55069;,
 -10.50576;37.68902;8.55069;,
 -10.50576;1.96830;9.99692;,
 -10.50576;37.68902;9.99692;,
 -10.17339;1.96830;10.64925;,
 -10.50576;1.96830;9.99692;,
 -10.17339;1.96830;7.89836;,
 -9.00337;1.96830;11.49932;,
 -6.90481;1.96830;11.16694;,
 -6.05474;1.96830;9.99692;,
 -6.05474;1.96830;8.55069;,
 -7.55714;1.96830;7.04829;,
 -8.28025;1.96830;6.93376;,
 -10.50576;1.96830;8.55069;,
 -10.50576;37.68902;9.99692;,
 -10.17339;37.68902;10.64925;,
 -10.17339;37.68902;7.89836;,
 -9.00337;37.68902;11.49932;,
 -6.90481;37.68902;11.16694;,
 -6.05474;37.68902;9.99692;,
 -6.05474;37.68902;8.55069;,
 -7.55714;37.68902;7.04829;,
 -8.28025;37.68902;6.93376;,
 -10.50576;37.68902;8.55069;,
 -10.50576;1.96830;-7.96353;,
 -10.17339;1.96830;-7.31120;,
 -10.17339;37.68902;-7.31120;,
 -10.50576;37.68902;-7.96353;,
 -9.00337;1.96830;-6.46113;,
 -9.00337;37.68902;-6.46113;,
 -6.90481;1.96830;-6.79351;,
 -6.90481;37.68902;-6.79351;,
 -6.05474;1.96830;-7.96353;,
 -6.05474;37.68902;-7.96353;,
 -6.05474;1.96830;-9.40975;,
 -6.05474;37.68902;-9.40975;,
 -7.55714;1.96830;-10.91215;,
 -7.55714;37.68902;-10.91215;,
 -8.28025;1.96830;-11.02668;,
 -8.28025;37.68902;-11.02668;,
 -10.17339;1.96830;-10.06208;,
 -10.17339;37.68902;-10.06208;,
 -10.50576;1.96830;-9.40975;,
 -10.50576;37.68902;-9.40975;,
 -10.50576;1.96830;-7.96353;,
 -10.50576;37.68902;-7.96353;,
 -10.17339;1.96830;-7.31120;,
 -10.50576;1.96830;-7.96353;,
 -10.17339;1.96830;-10.06208;,
 -9.00337;1.96830;-6.46113;,
 -6.90481;1.96830;-6.79351;,
 -6.05474;1.96830;-7.96353;,
 -6.05474;1.96830;-9.40975;,
 -7.55714;1.96830;-10.91215;,
 -8.28025;1.96830;-11.02668;,
 -10.50576;1.96830;-9.40975;,
 -10.50576;37.68902;-7.96353;,
 -10.17339;37.68902;-7.31120;,
 -10.17339;37.68902;-10.06208;,
 -9.00337;37.68902;-6.46113;,
 -6.90481;37.68902;-6.79351;,
 -6.05474;37.68902;-7.96353;,
 -6.05474;37.68902;-9.40975;,
 -7.55714;37.68902;-10.91215;,
 -8.28025;37.68902;-11.02668;,
 -10.50576;37.68902;-9.40975;,
 6.72193;1.96830;-7.96353;,
 7.05431;1.96830;-7.31120;,
 7.05431;37.68902;-7.31120;,
 6.72193;37.68902;-7.96353;,
 8.22433;1.96830;-6.46113;,
 8.22433;37.68902;-6.46113;,
 10.32289;1.96830;-6.79351;,
 10.32289;37.68902;-6.79351;,
 11.17296;1.96830;-7.96353;,
 11.17296;37.68902;-7.96353;,
 11.17296;1.96830;-9.40975;,
 11.17296;37.68902;-9.40975;,
 9.67056;1.96830;-10.91215;,
 9.67056;37.68902;-10.91215;,
 8.94744;1.96830;-11.02668;,
 8.94744;37.68902;-11.02668;,
 7.05431;1.96830;-10.06208;,
 7.05431;37.68902;-10.06208;,
 6.72193;1.96830;-9.40975;,
 6.72193;37.68902;-9.40975;,
 6.72193;1.96830;-7.96353;,
 6.72193;37.68902;-7.96353;,
 7.05431;1.96830;-7.31120;,
 6.72193;1.96830;-7.96353;,
 7.05431;1.96830;-10.06208;,
 8.22433;1.96830;-6.46113;,
 10.32289;1.96830;-6.79351;,
 11.17296;1.96830;-7.96353;,
 11.17296;1.96830;-9.40975;,
 9.67056;1.96830;-10.91215;,
 8.94744;1.96830;-11.02668;,
 6.72193;1.96830;-9.40975;,
 6.72193;37.68902;-7.96353;,
 7.05431;37.68902;-7.31120;,
 7.05431;37.68902;-10.06208;,
 8.22433;37.68902;-6.46113;,
 10.32289;37.68902;-6.79351;,
 11.17296;37.68902;-7.96353;,
 11.17296;37.68902;-9.40975;,
 9.67056;37.68902;-10.91215;,
 8.94744;37.68902;-11.02668;,
 6.72193;37.68902;-9.40975;,
 -15.89723;36.15283;-15.89723;,
 0.00000;50.55620;0.00000;,
 15.89723;36.15283;-15.89723;,
 15.89723;36.15283;-15.89723;,
 0.00000;50.55620;0.00000;,
 15.89723;36.15283;15.89723;,
 15.89723;36.15283;15.89723;,
 0.00000;50.55620;0.00000;,
 -15.89723;36.15283;15.89723;,
 -15.89723;36.15283;15.89723;,
 0.00000;50.55620;0.00000;,
 -15.89723;36.15283;-15.89723;,
 -15.89723;36.15283;15.89723;,
 -15.89723;36.15283;-15.89723;,
 15.89723;36.15283;-15.89723;,
 15.89723;36.15283;15.89723;,
 12.70108;10.30104;-11.38217;,
 -11.23888;10.30104;-11.38217;,
 -11.23888;11.57444;-11.38217;,
 12.70108;11.57444;-11.38217;,
 -11.23888;11.57444;11.38217;,
 12.70108;11.57444;11.38217;,
 -11.23888;10.30104;11.38217;,
 12.70108;10.30104;11.38217;,
 -11.23888;10.30104;-11.38217;,
 12.70108;10.30104;-11.38217;,
 -11.23888;10.30104;11.38217;,
 -11.23888;11.57444;11.38217;,
 12.70108;10.30104;11.38217;,
 12.70108;11.57444;11.38217;;
 
 150;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;12,0,3,13;,
 4;14,15,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;15,24,25,16;,
 4;26,14,17,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;39,38,40,41;,
 4;33,42,43,34;,
 4;44,32,35,45;,
 4;46,47,48,49;,
 4;49,48,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;47,56,57,48;,
 4;58,46,49,59;,
 4;60,61,62,63;,
 4;63,62,64,65;,
 4;65,64,66,67;,
 4;67,66,68,69;,
 4;61,70,71,62;,
 4;72,60,63,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;91,94,95,92;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 3;112,113,114;,
 3;115,112,114;,
 3;116,115,114;,
 3;117,116,114;,
 3;118,117,114;,
 3;119,118,114;,
 3;120,119,114;,
 3;113,121,114;,
 3;122,123,124;,
 3;123,125,124;,
 3;125,126,124;,
 3;126,127,124;,
 3;127,128,124;,
 3;128,129,124;,
 3;129,130,124;,
 3;131,122,124;,
 4;132,133,134,135;,
 4;133,136,137,134;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 3;154,155,156;,
 3;157,154,156;,
 3;158,157,156;,
 3;159,158,156;,
 3;160,159,156;,
 3;161,160,156;,
 3;162,161,156;,
 3;155,163,156;,
 3;164,165,166;,
 3;165,167,166;,
 3;167,168,166;,
 3;168,169,166;,
 3;169,170,166;,
 3;170,171,166;,
 3;171,172,166;,
 3;173,164,166;,
 4;174,175,176,177;,
 4;175,178,179,176;,
 4;178,180,181,179;,
 4;180,182,183,181;,
 4;182,184,185,183;,
 4;184,186,187,185;,
 4;186,188,189,187;,
 4;188,190,191,189;,
 4;190,192,193,191;,
 4;192,194,195,193;,
 3;196,197,198;,
 3;199,196,198;,
 3;200,199,198;,
 3;201,200,198;,
 3;202,201,198;,
 3;203,202,198;,
 3;204,203,198;,
 3;197,205,198;,
 3;206,207,208;,
 3;207,209,208;,
 3;209,210,208;,
 3;210,211,208;,
 3;211,212,208;,
 3;212,213,208;,
 3;213,214,208;,
 3;215,206,208;,
 4;216,217,218,219;,
 4;217,220,221,218;,
 4;220,222,223,221;,
 4;222,224,225,223;,
 4;224,226,227,225;,
 4;226,228,229,227;,
 4;228,230,231,229;,
 4;230,232,233,231;,
 4;232,234,235,233;,
 4;234,236,237,235;,
 3;238,239,240;,
 3;241,238,240;,
 3;242,241,240;,
 3;243,242,240;,
 3;244,243,240;,
 3;245,244,240;,
 3;246,245,240;,
 3;239,247,240;,
 3;248,249,250;,
 3;249,251,250;,
 3;251,252,250;,
 3;252,253,250;,
 3;253,254,250;,
 3;254,255,250;,
 3;255,256,250;,
 3;257,248,250;,
 3;258,259,260;,
 3;261,262,263;,
 3;264,265,266;,
 3;267,268,269;,
 4;270,271,272,273;,
 4;274,275,276,277;,
 4;277,276,278,279;,
 4;279,278,280,281;,
 4;281,280,282,283;,
 4;275,284,285,276;,
 4;286,274,277,287;;
 
 MeshMaterialList {
  1;
  150;
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
    "data\\TEXTURE\\UV\\Yagura.png";
   }
  }
 }
 MeshNormals {
  55;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000146;1.000000;0.000000;,
  -0.000020;1.000000;0.000000;,
  0.000051;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -0.972370;0.000000;0.233446;,
  -0.760406;0.000000;0.649448;,
  -0.233445;0.000000;0.972370;,
  0.522499;0.000000;0.852640;,
  0.951056;0.000000;0.309017;,
  0.923880;0.000000;-0.382683;,
  0.453990;0.000000;-0.891007;,
  -0.156436;0.000000;-0.987688;,
  -0.707107;0.000000;-0.707107;,
  -0.972370;0.000000;-0.233446;,
  -0.972371;0.000000;0.233440;,
  -0.760410;0.000000;0.649444;,
  -0.233445;0.000000;0.972370;,
  0.522499;0.000000;0.852640;,
  0.951056;0.000000;0.309017;,
  0.453991;0.000000;-0.891006;,
  -0.156434;0.000000;-0.987688;,
  -0.707110;0.000000;-0.707103;,
  -0.972371;0.000000;-0.233440;,
  -0.972371;0.000000;0.233440;,
  -0.760410;0.000000;0.649444;,
  0.522499;0.000000;0.852640;,
  0.951056;0.000000;0.309017;,
  0.923879;0.000000;-0.382684;,
  0.453991;0.000000;-0.891006;,
  -0.156433;0.000000;-0.987689;,
  -0.707110;0.000000;-0.707103;,
  -0.972371;0.000000;-0.233440;,
  -0.972370;0.000000;0.233446;,
  -0.760406;0.000000;0.649448;,
  -0.233445;0.000000;0.972370;,
  0.522499;0.000000;0.852640;,
  0.951056;0.000000;0.309017;,
  0.453990;0.000000;-0.891007;,
  -0.156435;0.000000;-0.987688;,
  -0.707107;0.000000;-0.707107;,
  -0.972370;0.000000;-0.233446;,
  -0.381447;0.842019;-0.381447;,
  0.381447;0.842019;-0.381447;,
  0.381447;0.842019;0.381447;,
  -0.381447;0.842019;0.381447;,
  0.000000;-1.000000;0.000000;,
  0.000105;-1.000000;-0.000000;,
  1.000000;0.000002;0.000000;,
  0.000018;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;;
  150;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;50,50,50,50;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;50,50,50,50;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;6,6,6,6;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;53,53,53,53;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;54,54,54,54;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,9,9,18;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,14,14,23;,
  4;14,24,24,14;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,19,19,27;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;28,29,29,28;,
  4;29,21,21,29;,
  4;21,30,30,21;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,28,28,36;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,32,32,41;,
  4;32,42,42,32;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,37,37,45;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;46,47,47;,
  3;47,47,48;,
  3;48,49,49;,
  3;49,49,46;,
  4;50,50,50,50;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;50,50,50,50;,
  4;6,6,6,6;,
  4;8,8,8,8;;
 }
 MeshTextureCoords {
  288;
  0.375000;0.810585;,
  0.625000;0.810585;,
  0.625000;0.759380;,
  0.375000;0.759380;,
  0.625000;0.708175;,
  0.375000;0.708175;,
  0.625000;0.656971;,
  0.375000;0.656971;,
  0.625000;0.605766;,
  0.375000;0.605766;,
  0.875000;0.810585;,
  0.875000;0.759380;,
  0.125000;0.810585;,
  0.125000;0.759380;,
  0.375000;0.723321;,
  0.625000;0.723321;,
  0.625000;0.696212;,
  0.375000;0.696212;,
  0.625000;0.669104;,
  0.375000;0.669104;,
  0.625000;0.641996;,
  0.375000;0.641996;,
  0.625000;0.614887;,
  0.375000;0.614887;,
  0.875000;0.723321;,
  0.875000;0.696212;,
  0.125000;0.723321;,
  0.125000;0.696212;,
  0.375000;0.780986;,
  0.625000;0.780986;,
  0.625000;0.737814;,
  0.375000;0.737814;,
  0.375000;0.780986;,
  0.625000;0.780986;,
  0.625000;0.737814;,
  0.375000;0.737814;,
  0.625000;0.694641;,
  0.375000;0.694641;,
  0.625000;0.651468;,
  0.375000;0.651468;,
  0.625000;0.608296;,
  0.375000;0.608296;,
  0.875000;0.780986;,
  0.875000;0.737814;,
  0.125000;0.780986;,
  0.125000;0.737814;,
  0.375000;0.780986;,
  0.625000;0.780986;,
  0.625000;0.737814;,
  0.375000;0.737814;,
  0.625000;0.694641;,
  0.375000;0.694641;,
  0.625000;0.651468;,
  0.375000;0.651468;,
  0.625000;0.608296;,
  0.375000;0.608296;,
  0.875000;0.780986;,
  0.875000;0.737814;,
  0.125000;0.780986;,
  0.125000;0.737814;,
  0.375000;0.780986;,
  0.625000;0.780986;,
  0.625000;0.737814;,
  0.375000;0.737814;,
  0.625000;0.694641;,
  0.375000;0.694641;,
  0.625000;0.651468;,
  0.375000;0.651468;,
  0.625000;0.608296;,
  0.375000;0.608296;,
  0.875000;0.780986;,
  0.875000;0.737814;,
  0.125000;0.780986;,
  0.125000;0.737814;,
  0.000000;0.997894;,
  1.000000;0.997894;,
  1.000000;0.849299;,
  0.000000;0.849299;,
  0.000000;0.997894;,
  1.000000;0.997894;,
  1.000000;0.849299;,
  0.000000;0.849299;,
  0.000000;0.997894;,
  1.000000;0.997894;,
  1.000000;0.849299;,
  0.000000;0.849299;,
  0.000000;0.997894;,
  1.000000;0.997894;,
  1.000000;0.849299;,
  0.000000;0.849299;,
  0.564151;0.545650;,
  0.564284;0.541284;,
  0.432993;0.537284;,
  0.432860;0.541649;,
  0.564551;0.532553;,
  0.433259;0.528553;,
  0.564950;0.519457;,
  0.433658;0.515457;,
  0.565216;0.510726;,
  0.433924;0.506726;,
  0.565482;0.501995;,
  0.434190;0.497995;,
  0.565881;0.488899;,
  0.434589;0.484898;,
  0.566014;0.484534;,
  0.434722;0.480533;,
  0.566413;0.471437;,
  0.435121;0.467437;,
  0.566546;0.467072;,
  0.435254;0.463071;,
  0.566812;0.458341;,
  0.435520;0.454340;,
  0.653469;0.460489;,
  0.638494;0.452275;,
  0.589321;0.458534;,
  0.672461;0.488377;,
  0.663219;0.537078;,
  0.635331;0.556069;,
  0.601606;0.555042;,
  0.567639;0.518939;,
  0.565482;0.501995;,
  0.604769;0.451247;,
  0.364669;0.443931;,
  0.349221;0.451218;,
  0.413370;0.453173;,
  0.328567;0.477898;,
  0.334826;0.527071;,
  0.361506;0.547725;,
  0.395231;0.548753;,
  0.431334;0.514786;,
  0.434518;0.498005;,
  0.398394;0.444959;,
  0.564151;0.545650;,
  0.564284;0.541284;,
  0.432993;0.537284;,
  0.432860;0.541649;,
  0.564551;0.532553;,
  0.433259;0.528553;,
  0.564950;0.519457;,
  0.433658;0.515457;,
  0.565216;0.510726;,
  0.433924;0.506726;,
  0.565482;0.501995;,
  0.434190;0.497995;,
  0.565881;0.488899;,
  0.434589;0.484898;,
  0.566014;0.484534;,
  0.434722;0.480533;,
  0.566413;0.471437;,
  0.435121;0.467437;,
  0.566546;0.467072;,
  0.435254;0.463071;,
  0.566812;0.458341;,
  0.435520;0.454340;,
  0.653469;0.460489;,
  0.638494;0.452275;,
  0.589321;0.458534;,
  0.672461;0.488377;,
  0.663219;0.537078;,
  0.635331;0.556069;,
  0.601606;0.555042;,
  0.567639;0.518939;,
  0.565482;0.501995;,
  0.604769;0.451247;,
  0.364669;0.443931;,
  0.349221;0.451218;,
  0.413370;0.453173;,
  0.328567;0.477898;,
  0.334826;0.527071;,
  0.361506;0.547725;,
  0.395231;0.548753;,
  0.431334;0.514786;,
  0.434518;0.498005;,
  0.398394;0.444959;,
  0.564151;0.545650;,
  0.564284;0.541284;,
  0.432993;0.537284;,
  0.432860;0.541649;,
  0.564551;0.532553;,
  0.433259;0.528553;,
  0.564950;0.519457;,
  0.433658;0.515457;,
  0.565216;0.510726;,
  0.433924;0.506726;,
  0.565482;0.501995;,
  0.434190;0.497995;,
  0.565881;0.488899;,
  0.434589;0.484898;,
  0.566014;0.484534;,
  0.434722;0.480533;,
  0.566413;0.471437;,
  0.435121;0.467437;,
  0.566546;0.467072;,
  0.435254;0.463071;,
  0.566812;0.458341;,
  0.435520;0.454340;,
  0.653469;0.460489;,
  0.638494;0.452275;,
  0.589321;0.458534;,
  0.672461;0.488377;,
  0.663219;0.537078;,
  0.635331;0.556069;,
  0.601606;0.555042;,
  0.567639;0.518939;,
  0.565482;0.501995;,
  0.604769;0.451247;,
  0.364669;0.443931;,
  0.349221;0.451218;,
  0.413370;0.453173;,
  0.328567;0.477898;,
  0.334826;0.527071;,
  0.361506;0.547725;,
  0.395231;0.548753;,
  0.431334;0.514786;,
  0.434518;0.498005;,
  0.398394;0.444959;,
  0.564151;0.545650;,
  0.564284;0.541284;,
  0.432993;0.537284;,
  0.432860;0.541649;,
  0.564551;0.532553;,
  0.433259;0.528553;,
  0.564950;0.519457;,
  0.433658;0.515457;,
  0.565216;0.510726;,
  0.433924;0.506726;,
  0.565482;0.501995;,
  0.434190;0.497995;,
  0.565881;0.488899;,
  0.434589;0.484898;,
  0.566014;0.484534;,
  0.434722;0.480533;,
  0.566413;0.471437;,
  0.435121;0.467437;,
  0.566546;0.467072;,
  0.435254;0.463071;,
  0.566812;0.458341;,
  0.435520;0.454340;,
  0.653469;0.460489;,
  0.638494;0.452275;,
  0.589321;0.458534;,
  0.672461;0.488377;,
  0.663219;0.537078;,
  0.635331;0.556069;,
  0.601606;0.555042;,
  0.567639;0.518939;,
  0.565482;0.501995;,
  0.604769;0.451247;,
  0.364669;0.443931;,
  0.349221;0.451218;,
  0.413370;0.453173;,
  0.328567;0.477898;,
  0.334826;0.527071;,
  0.361506;0.547725;,
  0.395231;0.548753;,
  0.431334;0.514786;,
  0.434518;0.498005;,
  0.398394;0.444959;,
  0.033597;0.232353;,
  0.966403;0.121600;,
  0.033597;0.010847;,
  0.006782;0.208620;,
  0.993218;0.113295;,
  0.006782;0.017971;,
  0.017458;0.169165;,
  0.982542;0.101383;,
  0.017458;0.033600;,
  0.007526;0.200209;,
  0.992474;0.110924;,
  0.007526;0.021639;,
  0.125000;0.233500;,
  0.375000;0.233500;,
  0.375000;0.191461;,
  0.125000;0.191461;,
  0.375000;0.723321;,
  0.625000;0.723321;,
  0.625000;0.696212;,
  0.375000;0.696212;,
  0.625000;0.669104;,
  0.375000;0.669104;,
  0.625000;0.641996;,
  0.375000;0.641996;,
  0.625000;0.614887;,
  0.375000;0.614887;,
  0.875000;0.723321;,
  0.875000;0.696212;,
  0.125000;0.723321;,
  0.125000;0.696212;;
 }
}
