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
 290;
 0.18238;-0.54126;-0.12523;,
 0.33321;-0.42358;-0.11307;,
 1.15040;-2.30030;0.91354;,
 0.75554;-2.60837;0.88173;,
 0.44735;-0.28074;-0.06575;,
 1.44932;-1.92652;1.03732;,
 0.51373;-0.12688;0.01201;,
 1.62303;-1.52366;1.24096;,
 0.52578;0.02307;0.11268;,
 1.65458;-1.13107;1.50450;,
 0.48233;0.15439;0.22637;,
 1.54083;-0.78727;1.80216;,
 0.38764;0.25425;0.34197;,
 1.29293;-0.52587;2.10481;,
 0.25099;0.31280;0.44813;,
 0.93516;-0.37249;2.38278;,
 0.08574;0.32442;0.53451;,
 0.50254;-0.34209;2.60892;,
 -0.09194;0.28791;0.59263;,
 0.03738;-0.43771;2.76103;,
 -0.26463;0.20684;0.61679;,
 -0.41473;-0.64994;2.82430;,
 -0.41544;0.08916;0.60463;,
 -0.80958;-0.95802;2.79245;,
 -0.52964;-0.05359;0.55736;,
 -1.10849;-1.33178;2.66869;,
 -0.59599;-0.20750;0.47958;,
 -1.28223;-1.73469;2.46505;,
 -0.60803;-0.35744;0.37890;,
 -1.31376;-2.12723;2.20151;,
 -0.56458;-0.48876;0.26522;,
 -1.20002;-2.47109;1.90383;,
 -0.46990;-0.58858;0.14964;,
 -0.95213;-2.73245;1.60123;,
 -0.33324;-0.64724;0.04343;,
 -0.59436;-2.88583;1.32324;,
 -0.16798;-0.65884;-0.04295;,
 -0.16172;-2.91621;1.09711;,
 0.00969;-0.62229;-0.10105;,
 0.30342;-2.82064;0.94497;,
 0.18238;-0.54126;-0.12523;,
 0.75554;-2.60837;0.88173;,
 1.18731;-5.79513;4.36096;,
 0.76244;-5.83817;4.04551;,
 1.51957;-5.61799;4.72794;,
 1.72667;-5.32400;5.11037;,
 1.78836;-4.94206;5.47086;,
 1.69858;-4.50954;5.77416;,
 1.46615;-4.06876;5.99047;,
 1.11378;-3.66284;6.09878;,
 0.67597;-3.33151;6.08833;,
 0.19561;-3.10725;5.96024;,
 -0.28030;-3.01200;5.72703;,
 -0.70518;-3.05504;5.41150;,
 -1.03742;-3.23219;5.04457;,
 -1.24455;-3.52613;4.66216;,
 -1.30623;-3.90807;4.30163;,
 -1.21646;-4.34061;3.99836;,
 -0.98401;-4.78143;3.78204;,
 -0.63164;-5.18733;3.67375;,
 -0.19384;-5.51862;3.68421;,
 0.28652;-5.74289;3.81224;,
 0.76244;-5.83817;4.04551;,
 -0.87242;-7.17485;6.62997;,
 -1.01260;-7.08787;6.36146;,
 -0.76571;-7.17384;6.90513;,
 -0.70281;-7.08504;7.15999;,
 -0.68998;-6.91710;7.36966;,
 -0.72847;-6.68656;7.51358;,
 -0.81444;-6.41581;7.57762;,
 -0.93957;-6.13143;7.55561;,
 -1.09150;-5.86131;7.44961;,
 -1.25545;-5.63183;7.27004;,
 -1.41536;-5.46546;7.03449;,
 -1.55553;-5.37852;6.76597;,
 -1.66227;-5.37948;6.49083;,
 -1.72512;-5.46830;6.23594;,
 -1.73794;-5.63619;6.02632;,
 -1.69949;-5.86683;5.88239;,
 -1.61348;-6.13755;5.81830;,
 -1.48839;-6.42192;5.84035;,
 -1.33644;-6.69204;5.94632;,
 -1.17249;-6.92150;6.12589;,
 -1.01260;-7.08787;6.36146;,
 -2.15038;-7.56337;7.61568;,
 -2.19593;-7.53511;7.52839;,
 -2.11571;-7.56300;7.70502;,
 -2.09527;-7.53421;7.78788;,
 -2.09109;-7.47962;7.85598;,
 -2.10360;-7.40474;7.90273;,
 -2.13153;-7.31672;7.92355;,
 -2.17215;-7.22432;7.91637;,
 -2.22156;-7.13651;7.88189;,
 -2.27484;-7.06199;7.82357;,
 -2.32677;-7.00794;7.74707;,
 -2.37231;-6.97968;7.65979;,
 -2.40702;-6.98000;7.57046;,
 -2.42742;-7.00887;7.48756;,
 -2.43160;-7.06341;7.41949;,
 -2.41909;-7.13835;7.37272;,
 -2.39115;-7.22632;7.35187;,
 -2.35051;-7.31871;7.35909;,
 -2.30116;-7.40646;7.39355;,
 -2.24786;-7.48104;7.45190;,
 -2.19593;-7.53511;7.52839;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -0.06963;0.02979;0.02925;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 -2.34118;-7.34736;7.70941;,
 1.21518;-1.28477;1.28027;,
 1.29115;-1.24987;1.28713;,
 1.35278;-2.11675;1.74891;,
 1.15390;-2.20806;1.73098;,
 1.35342;-1.20065;1.30868;,
 1.51579;-1.98794;1.80526;,
 1.39589;-1.14194;1.34276;,
 1.62698;-1.83422;1.89454;,
 1.41441;-1.07947;1.38608;,
 1.67548;-1.67063;2.00796;,
 1.40717;-1.01933;1.43440;,
 1.65650;-1.51322;2.13444;,
 1.37486;-0.96745;1.48297;,
 1.57194;-1.37737;2.26160;,
 1.32068;-0.92889;1.52703;,
 1.43008;-1.27640;2.37699;,
 1.24989;-0.90741;1.56230;,
 1.24477;-1.22017;2.46931;,
 1.16945;-0.90513;1.58531;,
 1.03418;-1.21420;2.52953;,
 1.08724;-0.92225;1.59379;,
 0.81891;-1.25907;2.55174;,
 1.01127;-0.95714;1.58694;,
 0.62002;-1.35038;2.53380;,
 0.94900;-1.00633;1.56540;,
 0.45703;-1.47921;2.47745;,
 0.90653;-1.06507;1.53132;,
 0.34583;-1.63294;2.38817;,
 0.88802;-1.12754;1.48799;,
 0.29736;-1.79651;2.27475;,
 0.89525;-1.18768;1.43968;,
 0.31631;-1.95394;2.14826;,
 0.92756;-1.23956;1.39111;,
 0.40086;-2.08978;2.02113;,
 0.98173;-1.27813;1.34703;,
 0.54273;-2.19073;1.90573;,
 1.05251;-1.29962;1.31176;,
 0.72805;-2.24696;1.81342;,
 1.13295;-1.30188;1.28877;,
 0.93863;-2.25293;1.75320;,
 1.21518;-1.28477;1.28027;,
 1.15390;-2.20806;1.73098;,
 1.00043;-5.00522;6.76617;,
 0.83451;-4.98308;6.62400;,
 1.14205;-4.96147;6.92903;,
 1.24550;-4.85616;7.09662;,
 1.30063;-4.69961;7.25251;,
 1.30208;-4.50710;7.38144;,
 1.24970;-4.29753;7.47080;,
 1.14859;-4.09136;7.51189;,
 1.00868;-3.90880;7.50059;,
 0.84366;-3.76768;7.43809;,
 0.66966;-3.68187;7.33047;,
 0.50373;-3.65976;7.18827;,
 0.36214;-3.70348;7.02541;,
 0.25869;-3.80879;6.85783;,
 0.20355;-3.96534;6.70195;,
 0.20208;-4.15786;6.57301;,
 0.25449;-4.36745;6.48364;,
 0.35558;-4.57362;6.44260;,
 0.49549;-4.75617;6.45389;,
 0.66051;-4.89727;6.51635;,
 0.83451;-4.98308;6.62400;,
 -0.12221;-5.37498;7.72764;,
 -0.15704;-5.32575;7.60908;,
 -0.09081;-5.38380;7.84832;,
 -0.06589;-5.35141;7.95934;,
 -0.04991;-5.28096;8.04990;,
 -0.04443;-5.17933;8.11104;,
 -0.04999;-5.05649;8.13683;,
 -0.06606;-4.92441;8.12475;,
 -0.09103;-4.79610;8.07594;,
 -0.12247;-4.68406;7.99521;,
 -0.15734;-4.59926;7.89046;,
 -0.19217;-4.55005;7.77193;,
 -0.22358;-4.54120;7.65127;,
 -0.24849;-4.57360;7.54021;,
 -0.26446;-4.64405;7.44970;,
 -0.26994;-4.74569;7.38852;,
 -0.26437;-4.86854;7.36272;,
 -0.24831;-5.00060;7.37481;,
 -0.22334;-5.12893;7.42363;,
 -0.19188;-5.24096;7.50435;,
 -0.15704;-5.32575;7.60908;,
 -0.74240;-5.40915;8.13963;,
 -0.75372;-5.39314;8.10111;,
 -0.73220;-5.41200;8.17883;,
 -0.72409;-5.40150;8.21491;,
 -0.71891;-5.37859;8.24431;,
 -0.71714;-5.34558;8.26419;,
 -0.71893;-5.30565;8.27259;,
 -0.72414;-5.26274;8.26868;,
 -0.73225;-5.22103;8.25278;,
 -0.74250;-5.18463;8.22655;,
 -0.75380;-5.15709;8.19252;,
 -0.76512;-5.14109;8.15402;,
 -0.77534;-5.13822;8.11482;,
 -0.78343;-5.14875;8.07870;,
 -0.78861;-5.17164;8.04930;,
 -0.79040;-5.20466;8.02944;,
 -0.78859;-5.24459;8.02104;,
 -0.78336;-5.28749;8.02499;,
 -0.77526;-5.32918;8.04087;,
 -0.76504;-5.36559;8.06709;,
 -0.75372;-5.39314;8.10111;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 1.17340;-1.01861;1.34215;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;,
 -0.79924;-5.29895;8.17709;;
 
 240;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;3,2,42,43;,
 4;2,5,44,42;,
 4;5,7,45,44;,
 4;7,9,46,45;,
 4;9,11,47,46;,
 4;11,13,48,47;,
 4;13,15,49,48;,
 4;15,17,50,49;,
 4;17,19,51,50;,
 4;19,21,52,51;,
 4;21,23,53,52;,
 4;23,25,54,53;,
 4;25,27,55,54;,
 4;27,29,56,55;,
 4;29,31,57,56;,
 4;31,33,58,57;,
 4;33,35,59,58;,
 4;35,37,60,59;,
 4;37,39,61,60;,
 4;39,41,62,61;,
 4;43,42,63,64;,
 4;42,44,65,63;,
 4;44,45,66,65;,
 4;45,46,67,66;,
 4;46,47,68,67;,
 4;47,48,69,68;,
 4;48,49,70,69;,
 4;49,50,71,70;,
 4;50,51,72,71;,
 4;51,52,73,72;,
 4;52,53,74,73;,
 4;53,54,75,74;,
 4;54,55,76,75;,
 4;55,56,77,76;,
 4;56,57,78,77;,
 4;57,58,79,78;,
 4;58,59,80,79;,
 4;59,60,81,80;,
 4;60,61,82,81;,
 4;61,62,83,82;,
 4;64,63,84,85;,
 4;63,65,86,84;,
 4;65,66,87,86;,
 4;66,67,88,87;,
 4;67,68,89,88;,
 4;68,69,90,89;,
 4;69,70,91,90;,
 4;70,71,92,91;,
 4;71,72,93,92;,
 4;72,73,94,93;,
 4;73,74,95,94;,
 4;74,75,96,95;,
 4;75,76,97,96;,
 4;76,77,98,97;,
 4;77,78,99,98;,
 4;78,79,100,99;,
 4;79,80,101,100;,
 4;80,81,102,101;,
 4;81,82,103,102;,
 4;82,83,104,103;,
 3;1,0,105;,
 3;4,1,106;,
 3;6,4,107;,
 3;8,6,108;,
 3;10,8,109;,
 3;12,10,110;,
 3;14,12,111;,
 3;16,14,112;,
 3;18,16,113;,
 3;20,18,114;,
 3;22,20,115;,
 3;24,22,116;,
 3;26,24,117;,
 3;28,26,118;,
 3;30,28,119;,
 3;32,30,120;,
 3;34,32,121;,
 3;36,34,122;,
 3;38,36,123;,
 3;40,38,124;,
 3;85,84,125;,
 3;84,86,126;,
 3;86,87,127;,
 3;87,88,128;,
 3;88,89,129;,
 3;89,90,130;,
 3;90,91,131;,
 3;91,92,132;,
 3;92,93,133;,
 3;93,94,134;,
 3;94,95,135;,
 3;95,96,136;,
 3;96,97,137;,
 3;97,98,138;,
 3;98,99,139;,
 3;99,100,140;,
 3;100,101,141;,
 3;101,102,142;,
 3;102,103,143;,
 3;103,104,144;,
 4;145,146,147,148;,
 4;146,149,150,147;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;159,161,162,160;,
 4;161,163,164,162;,
 4;163,165,166,164;,
 4;165,167,168,166;,
 4;167,169,170,168;,
 4;169,171,172,170;,
 4;171,173,174,172;,
 4;173,175,176,174;,
 4;175,177,178,176;,
 4;177,179,180,178;,
 4;179,181,182,180;,
 4;181,183,184,182;,
 4;183,185,186,184;,
 4;148,147,187,188;,
 4;147,150,189,187;,
 4;150,152,190,189;,
 4;152,154,191,190;,
 4;154,156,192,191;,
 4;156,158,193,192;,
 4;158,160,194,193;,
 4;160,162,195,194;,
 4;162,164,196,195;,
 4;164,166,197,196;,
 4;166,168,198,197;,
 4;168,170,199,198;,
 4;170,172,200,199;,
 4;172,174,201,200;,
 4;174,176,202,201;,
 4;176,178,203,202;,
 4;178,180,204,203;,
 4;180,182,205,204;,
 4;182,184,206,205;,
 4;184,186,207,206;,
 4;188,187,208,209;,
 4;187,189,210,208;,
 4;189,190,211,210;,
 4;190,191,212,211;,
 4;191,192,213,212;,
 4;192,193,214,213;,
 4;193,194,215,214;,
 4;194,195,216,215;,
 4;195,196,217,216;,
 4;196,197,218,217;,
 4;197,198,219,218;,
 4;198,199,220,219;,
 4;199,200,221,220;,
 4;200,201,222,221;,
 4;201,202,223,222;,
 4;202,203,224,223;,
 4;203,204,225,224;,
 4;204,205,226,225;,
 4;205,206,227,226;,
 4;206,207,228,227;,
 4;209,208,229,230;,
 4;208,210,231,229;,
 4;210,211,232,231;,
 4;211,212,233,232;,
 4;212,213,234,233;,
 4;213,214,235,234;,
 4;214,215,236,235;,
 4;215,216,237,236;,
 4;216,217,238,237;,
 4;217,218,239,238;,
 4;218,219,240,239;,
 4;219,220,241,240;,
 4;220,221,242,241;,
 4;221,222,243,242;,
 4;222,223,244,243;,
 4;223,224,245,244;,
 4;224,225,246,245;,
 4;225,226,247,246;,
 4;226,227,248,247;,
 4;227,228,249,248;,
 3;146,145,250;,
 3;149,146,251;,
 3;151,149,252;,
 3;153,151,253;,
 3;155,153,254;,
 3;157,155,255;,
 3;159,157,256;,
 3;161,159,257;,
 3;163,161,258;,
 3;165,163,259;,
 3;167,165,260;,
 3;169,167,261;,
 3;171,169,262;,
 3;173,171,263;,
 3;175,173,264;,
 3;177,175,265;,
 3;179,177,266;,
 3;181,179,267;,
 3;183,181,268;,
 3;185,183,269;,
 3;230,229,270;,
 3;229,231,271;,
 3;231,232,272;,
 3;232,233,273;,
 3;233,234,274;,
 3;234,235,275;,
 3;235,236,276;,
 3;236,237,277;,
 3;237,238,278;,
 3;238,239,279;,
 3;239,240,280;,
 3;240,241,281;,
 3;241,242,282;,
 3;242,243,283;,
 3;243,244,284;,
 3;244,245,285;,
 3;245,246,286;,
 3;246,247,287;,
 3;247,248,288;,
 3;248,249,289;;
 
 MeshMaterialList {
  1;
  240;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  214;
  0.026053;-0.098935;-0.994753;,
  0.221440;0.000555;-0.975174;,
  0.387527;0.150492;-0.909492;,
  0.499519;0.341079;-0.796333;,
  0.532862;0.550555;-0.642610;,
  0.473773;0.746383;-0.467388;,
  0.329252;0.895808;-0.298531;,
  0.126077;0.978587;-0.162705;,
  -0.101796;0.991885;-0.076169;,
  -0.325049;0.944709;-0.043223;,
  -0.522702;0.850374;-0.060388;,
  -0.681034;0.722319;-0.120201;,
  -0.791305;0.572888;-0.213628;,
  -0.848150;0.413875;-0.330679;,
  -0.849456;0.256915;-0.460890;,
  -0.796602;0.113101;-0.593829;,
  -0.694401;-0.007189;-0.719553;,
  -0.550447;-0.095109;-0.829435;,
  -0.374438;-0.143364;-0.916102;,
  -0.177920;-0.146108;-0.973138;,
  0.292814;-0.526270;-0.798310;,
  0.564980;-0.409499;-0.716316;,
  0.782236;-0.233681;-0.577494;,
  0.919146;-0.014165;-0.393661;,
  0.956832;0.226435;-0.182211;,
  0.887300;0.459958;0.033724;,
  0.717490;0.658080;0.228340;,
  0.468571;0.798242;0.378484;,
  0.170708;0.866909;0.468325;,
  -0.142458;0.859427;0.491010;,
  -0.437707;0.779395;0.448281;,
  -0.686305;0.638128;0.348967;,
  -0.867518;0.452762;0.205960;,
  -0.969423;0.243126;0.033307;,
  -0.987400;0.028500;-0.155656;,
  -0.921652;-0.173616;-0.347009;,
  -0.777276;-0.347403;-0.524551;,
  -0.564745;-0.479595;-0.671604;,
  -0.300134;-0.558912;-0.773005;,
  -0.005340;-0.576241;-0.817263;,
  0.243229;-0.797738;-0.551773;,
  0.526154;-0.749539;-0.401688;,
  0.756305;-0.625521;-0.191642;,
  0.899966;-0.432774;0.052611;,
  0.935256;-0.193477;0.296418;,
  0.860104;0.059407;0.506647;,
  0.690326;0.292595;0.661693;,
  0.450328;0.480913;0.752282;,
  0.166734;0.608018;0.776218;,
  -0.133005;0.664415;0.735434;,
  -0.420830;0.647172;0.635666;,
  -0.669682;0.560485;0.487219;,
  -0.857018;0.415717;0.304465;,
  -0.967753;0.229356;0.104167;,
  -0.994894;0.021898;-0.098524;,
  -0.938577;-0.187993;-0.289366;,
  -0.804304;-0.385480;-0.452218;,
  -0.602496;-0.556999;-0.571621;,
  -0.347585;-0.690631;-0.634203;,
  -0.057860;-0.774748;-0.629617;,
  0.020029;-0.910030;-0.414058;,
  0.250437;-0.943529;-0.216875;,
  0.449299;-0.892327;0.043387;,
  0.579984;-0.741294;0.337789;,
  0.610506;-0.502212;0.612427;,
  0.536670;-0.221296;0.814256;,
  0.383182;0.047680;0.922442;,
  0.181898;0.271368;0.945131;,
  -0.042788;0.437572;0.898165;,
  -0.274055;0.542949;0.793788;,
  -0.497445;0.585408;0.640192;,
  -0.696193;0.562552;0.445926;,
  -0.851244;0.474541;0.224041;,
  -0.944791;0.327627;-0.005529;,
  -0.965735;0.138004;-0.219797;,
  -0.914344;-0.073853;-0.398147;,
  -0.800179;-0.289277;-0.525388;,
  -0.636841;-0.491941;-0.593657;,
  -0.437841;-0.669903;-0.599604;,
  -0.214934;-0.813189;-0.540858;,
  -0.447006;-0.877981;-0.171275;,
  -0.317845;-0.948142;-0.000789;,
  0.312685;-0.947511;0.066718;,
  0.435378;-0.814835;0.382740;,
  0.464378;-0.572383;0.675819;,
  0.391462;-0.273462;0.878622;,
  0.245248;0.013643;0.969364;,
  -0.362005;0.030748;0.931669;,
  -0.491051;0.174449;0.853485;,
  -0.620029;0.264896;0.738508;,
  -0.742640;0.305156;0.596126;,
  -0.850940;0.296517;0.433566;,
  -0.935682;0.239946;0.258698;,
  -0.986698;0.139391;0.083643;,
  -0.997103;0.003692;-0.075976;,
  -0.966383;-0.154114;-0.205796;,
  -0.900300;-0.319897;-0.295170;,
  -0.807754;-0.482345;-0.338935;,
  -0.697273;-0.633809;-0.334808;,
  -0.575396;-0.768266;-0.280511;,
  -0.336843;0.554030;-0.761306;,
  -0.858648;-0.371209;0.353450;,
  0.031826;-0.120134;-0.992247;,
  0.250224;-0.079957;-0.964881;,
  0.455121;0.021347;-0.890174;,
  0.615670;0.182617;-0.766552;,
  0.697239;0.387692;-0.602953;,
  0.675890;0.603641;-0.422837;,
  0.553961;0.791405;-0.258469;,
  0.359569;0.922988;-0.137125;,
  0.130570;0.988847;-0.071649;,
  -0.100108;0.993058;-0.061765;,
  -0.309728;0.945584;-0.099701;,
  -0.483657;0.857600;-0.174924;,
  -0.613288;0.739800;-0.276720;,
  -0.693790;0.602395;-0.394684;,
  -0.723163;0.455292;-0.519370;,
  -0.701877;0.307782;-0.642369;,
  -0.632214;0.169127;-0.756109;,
  -0.517916;0.048045;-0.854081;,
  -0.364045;-0.046693;-0.930210;,
  -0.177665;-0.105918;-0.978374;,
  0.167099;-0.681010;-0.712954;,
  0.477261;-0.608082;-0.634397;,
  0.734486;-0.456995;-0.501684;,
  0.910507;-0.247018;-0.331602;,
  0.989587;-0.000549;-0.143933;,
  0.965490;0.257412;0.039608;,
  0.843180;0.500011;0.197574;,
  0.637853;0.703459;0.313512;,
  0.372284;0.847745;0.377800;,
  0.072277;0.919027;0.387512;,
  -0.235000;0.908962;0.344330;,
  -0.516028;0.817790;0.254823;,
  -0.739731;0.660030;0.130989;,
  -0.888783;0.458120;-0.013815;,
  -0.957890;0.232323;-0.168741;,
  -0.945930;-0.000455;-0.324370;,
  -0.853881;-0.223396;-0.470086;,
  -0.685080;-0.420749;-0.594673;,
  -0.447063;-0.574902;-0.685290;,
  -0.154550;-0.667230;-0.728641;,
  0.043781;-0.892640;-0.448640;,
  0.335694;-0.890113;-0.308236;,
  0.589595;-0.799173;-0.117047;,
  0.774238;-0.624900;0.100277;,
  0.868098;-0.383951;0.314623;,
  0.860746;-0.104131;0.498271;,
  0.755125;0.179872;0.630422;,
  0.565580;0.435699;0.700204;,
  0.315310;0.635671;0.704629;,
  0.031031;0.760574;0.648509;,
  -0.260444;0.799640;0.541059;,
  -0.528189;0.751405;0.395483;,
  -0.744396;0.627619;0.227965;,
  -0.892874;0.447041;0.054122;,
  -0.966511;0.229507;-0.114818;,
  -0.962865;-0.007619;-0.269874;,
  -0.882503;-0.247867;-0.399689;,
  -0.729797;-0.474060;-0.492609;,
  -0.514247;-0.668312;-0.537502;,
  -0.249909;-0.813501;-0.525131;,
  -0.176771;-0.888259;-0.423967;,
  0.034989;-0.978580;-0.202871;,
  0.230208;-0.970139;0.076383;,
  0.376546;-0.846641;0.376048;,
  0.447254;-0.621463;0.643232;,
  0.434620;-0.338128;0.834730;,
  0.349548;-0.045564;0.935810;,
  0.209620;0.222502;0.952130;,
  0.032011;0.446569;0.894176;,
  -0.167375;0.613846;0.771478;,
  -0.371563;0.713727;0.593746;,
  -0.560852;0.737943;0.375348;,
  -0.715795;0.684817;0.136614;,
  -0.821644;0.561501;-0.098071;,
  -0.870622;0.384453;-0.306940;,
  -0.863139;0.172162;-0.474712;,
  -0.804411;-0.059632;-0.591072;,
  -0.700338;-0.296148;-0.649479;,
  -0.556655;-0.523850;-0.644761;,
  -0.379230;-0.727845;-0.571337;,
  -0.645006;-0.728212;-0.231679;,
  -0.545947;-0.836486;-0.047261;,
  0.087441;-0.992543;0.084923;,
  0.225645;-0.884761;0.407776;,
  0.297638;-0.653586;0.695871;,
  0.289364;-0.350273;0.890830;,
  0.212882;-0.039611;0.976275;,
  -0.393530;0.147241;0.907444;,
  -0.481188;0.323721;0.814655;,
  -0.579855;0.445437;0.682169;,
  -0.681344;0.513270;0.521847;,
  -0.777086;0.527036;0.344050;,
  -0.858271;0.487758;0.159570;,
  -0.916501;0.399644;-0.017634;,
  -0.946680;0.271525;-0.173413;,
  -0.948023;0.114892;-0.296737;,
  -0.923122;-0.058211;-0.380075;,
  -0.876490;-0.237117;-0.418976;,
  -0.812603;-0.413800;-0.410422;,
  -0.734705;-0.580996;-0.350217;,
  -0.171448;0.607374;-0.775695;,
  -0.957426;-0.115100;0.264740;,
  -0.650204;-0.686492;0.325519;,
  -0.626459;-0.634195;0.453151;,
  -0.619427;-0.543050;0.566927;,
  -0.630593;-0.426571;0.648375;,
  -0.658730;-0.303666;0.688376;,
  -0.833616;-0.490408;0.254135;,
  -0.805070;-0.445546;0.391601;,
  -0.781462;-0.355214;0.512972;,
  -0.766843;-0.233194;0.597974;,
  -0.764951;-0.100588;0.636185;;
  240;
  4;0,1,21,20;,
  4;1,2,22,21;,
  4;2,3,23,22;,
  4;3,4,24,23;,
  4;4,5,25,24;,
  4;5,6,26,25;,
  4;6,7,27,26;,
  4;7,8,28,27;,
  4;8,9,29,28;,
  4;9,10,30,29;,
  4;10,11,31,30;,
  4;11,12,32,31;,
  4;12,13,33,32;,
  4;13,14,34,33;,
  4;14,15,35,34;,
  4;15,16,36,35;,
  4;16,17,37,36;,
  4;17,18,38,37;,
  4;18,19,39,38;,
  4;19,0,20,39;,
  4;20,21,41,40;,
  4;21,22,42,41;,
  4;22,23,43,42;,
  4;23,24,44,43;,
  4;24,25,45,44;,
  4;25,26,46,45;,
  4;26,27,47,46;,
  4;27,28,48,47;,
  4;28,29,49,48;,
  4;29,30,50,49;,
  4;30,31,51,50;,
  4;31,32,52,51;,
  4;32,33,53,52;,
  4;33,34,54,53;,
  4;34,35,55,54;,
  4;35,36,56,55;,
  4;36,37,57,56;,
  4;37,38,58,57;,
  4;38,39,59,58;,
  4;39,20,40,59;,
  4;40,41,61,60;,
  4;41,42,62,61;,
  4;42,43,63,62;,
  4;43,44,64,63;,
  4;44,45,65,64;,
  4;45,46,66,65;,
  4;46,47,67,66;,
  4;47,48,68,67;,
  4;48,49,69,68;,
  4;49,50,70,69;,
  4;50,51,71,70;,
  4;51,52,72,71;,
  4;52,53,73,72;,
  4;53,54,74,73;,
  4;54,55,75,74;,
  4;55,56,76,75;,
  4;56,57,77,76;,
  4;57,58,78,77;,
  4;58,59,79,78;,
  4;59,40,60,79;,
  4;60,61,81,80;,
  4;61,62,82,81;,
  4;62,63,83,82;,
  4;63,64,84,83;,
  4;64,65,85,84;,
  4;65,66,86,85;,
  4;66,67,87,86;,
  4;67,68,88,87;,
  4;68,69,89,88;,
  4;69,70,90,89;,
  4;70,71,91,90;,
  4;71,72,92,91;,
  4;72,73,93,92;,
  4;73,74,94,93;,
  4;74,75,95,94;,
  4;75,76,96,95;,
  4;76,77,97,96;,
  4;77,78,98,97;,
  4;78,79,99,98;,
  4;79,60,80,99;,
  3;1,0,100;,
  3;2,1,100;,
  3;3,2,100;,
  3;4,3,100;,
  3;5,4,100;,
  3;6,5,100;,
  3;7,6,100;,
  3;8,7,100;,
  3;9,8,100;,
  3;10,9,100;,
  3;11,10,100;,
  3;12,11,100;,
  3;13,12,100;,
  3;14,13,100;,
  3;15,14,100;,
  3;16,15,100;,
  3;17,16,100;,
  3;18,17,100;,
  3;19,18,100;,
  3;0,19,100;,
  3;80,81,101;,
  3;81,204,101;,
  3;204,205,101;,
  3;205,206,101;,
  3;206,207,101;,
  3;207,208,101;,
  3;208,87,101;,
  3;87,88,101;,
  3;88,89,101;,
  3;89,90,101;,
  3;90,91,101;,
  3;91,92,101;,
  3;92,93,101;,
  3;93,94,101;,
  3;94,95,101;,
  3;95,96,101;,
  3;96,97,101;,
  3;97,98,101;,
  3;98,99,101;,
  3;99,80,101;,
  4;102,103,123,122;,
  4;103,104,124,123;,
  4;104,105,125,124;,
  4;105,106,126,125;,
  4;106,107,127,126;,
  4;107,108,128,127;,
  4;108,109,129,128;,
  4;109,110,130,129;,
  4;110,111,131,130;,
  4;111,112,132,131;,
  4;112,113,133,132;,
  4;113,114,134,133;,
  4;114,115,135,134;,
  4;115,116,136,135;,
  4;116,117,137,136;,
  4;117,118,138,137;,
  4;118,119,139,138;,
  4;119,120,140,139;,
  4;120,121,141,140;,
  4;121,102,122,141;,
  4;122,123,143,142;,
  4;123,124,144,143;,
  4;124,125,145,144;,
  4;125,126,146,145;,
  4;126,127,147,146;,
  4;127,128,148,147;,
  4;128,129,149,148;,
  4;129,130,150,149;,
  4;130,131,151,150;,
  4;131,132,152,151;,
  4;132,133,153,152;,
  4;133,134,154,153;,
  4;134,135,155,154;,
  4;135,136,156,155;,
  4;136,137,157,156;,
  4;137,138,158,157;,
  4;138,139,159,158;,
  4;139,140,160,159;,
  4;140,141,161,160;,
  4;141,122,142,161;,
  4;142,143,163,162;,
  4;143,144,164,163;,
  4;144,145,165,164;,
  4;145,146,166,165;,
  4;146,147,167,166;,
  4;147,148,168,167;,
  4;148,149,169,168;,
  4;149,150,170,169;,
  4;150,151,171,170;,
  4;151,152,172,171;,
  4;152,153,173,172;,
  4;153,154,174,173;,
  4;154,155,175,174;,
  4;155,156,176,175;,
  4;156,157,177,176;,
  4;157,158,178,177;,
  4;158,159,179,178;,
  4;159,160,180,179;,
  4;160,161,181,180;,
  4;161,142,162,181;,
  4;162,163,183,182;,
  4;163,164,184,183;,
  4;164,165,185,184;,
  4;165,166,186,185;,
  4;166,167,187,186;,
  4;167,168,188,187;,
  4;168,169,189,188;,
  4;169,170,190,189;,
  4;170,171,191,190;,
  4;171,172,192,191;,
  4;172,173,193,192;,
  4;173,174,194,193;,
  4;174,175,195,194;,
  4;175,176,196,195;,
  4;176,177,197,196;,
  4;177,178,198,197;,
  4;178,179,199,198;,
  4;179,180,200,199;,
  4;180,181,201,200;,
  4;181,162,182,201;,
  3;103,102,202;,
  3;104,103,202;,
  3;105,104,202;,
  3;106,105,202;,
  3;107,106,202;,
  3;108,107,202;,
  3;109,108,202;,
  3;110,109,202;,
  3;111,110,202;,
  3;112,111,202;,
  3;113,112,202;,
  3;114,113,202;,
  3;115,114,202;,
  3;116,115,202;,
  3;117,116,202;,
  3;118,117,202;,
  3;119,118,202;,
  3;120,119,202;,
  3;121,120,202;,
  3;102,121,202;,
  3;182,183,203;,
  3;183,209,203;,
  3;209,210,203;,
  3;210,211,203;,
  3;211,212,203;,
  3;212,213,203;,
  3;213,189,203;,
  3;189,190,203;,
  3;190,191,203;,
  3;191,192,203;,
  3;192,193,203;,
  3;193,194,203;,
  3;194,195,203;,
  3;195,196,203;,
  3;196,197,203;,
  3;197,198,203;,
  3;198,199,203;,
  3;199,200,203;,
  3;200,201,203;,
  3;201,182,203;;
 }
 MeshTextureCoords {
  290;
  0.415805;0.194577;,
  0.424225;0.194577;,
  0.424225;0.160900;,
  0.415805;0.160900;,
  0.432644;0.194577;,
  0.432644;0.160900;,
  0.441064;0.194577;,
  0.441064;0.160900;,
  0.449483;0.194577;,
  0.449483;0.160900;,
  0.457903;0.194577;,
  0.457903;0.160900;,
  0.466322;0.194577;,
  0.466322;0.160900;,
  0.474742;0.194577;,
  0.474742;0.160900;,
  0.483161;0.194577;,
  0.483161;0.160900;,
  0.491581;0.194577;,
  0.491581;0.160900;,
  0.500000;0.194577;,
  0.500000;0.160900;,
  0.508420;0.194577;,
  0.508420;0.160900;,
  0.516839;0.194577;,
  0.516839;0.160900;,
  0.525258;0.194577;,
  0.525258;0.160900;,
  0.533678;0.194577;,
  0.533678;0.160900;,
  0.542097;0.194577;,
  0.542097;0.160900;,
  0.550517;0.194577;,
  0.550517;0.160900;,
  0.558936;0.194577;,
  0.558936;0.160900;,
  0.567356;0.194577;,
  0.567356;0.160900;,
  0.575775;0.194577;,
  0.575775;0.160900;,
  0.584195;0.194577;,
  0.584195;0.160900;,
  0.424225;0.127222;,
  0.415805;0.127222;,
  0.432644;0.127222;,
  0.441064;0.127222;,
  0.449483;0.127222;,
  0.457903;0.127222;,
  0.466322;0.127222;,
  0.474742;0.127222;,
  0.483161;0.127222;,
  0.491581;0.127222;,
  0.500000;0.127222;,
  0.508420;0.127222;,
  0.516839;0.127222;,
  0.525258;0.127222;,
  0.533678;0.127222;,
  0.542097;0.127222;,
  0.550517;0.127222;,
  0.558936;0.127222;,
  0.567356;0.127222;,
  0.575775;0.127222;,
  0.584195;0.127222;,
  0.424225;0.110383;,
  0.415805;0.110383;,
  0.432644;0.110383;,
  0.441064;0.110383;,
  0.449483;0.110383;,
  0.457903;0.110383;,
  0.466322;0.110383;,
  0.474742;0.110383;,
  0.483161;0.110383;,
  0.491581;0.110383;,
  0.500000;0.110383;,
  0.508420;0.110383;,
  0.516839;0.110383;,
  0.525258;0.110383;,
  0.533678;0.110383;,
  0.542097;0.110383;,
  0.550517;0.110383;,
  0.558936;0.110383;,
  0.567356;0.110383;,
  0.575775;0.110383;,
  0.584195;0.110383;,
  0.424225;0.059866;,
  0.415805;0.059866;,
  0.432644;0.059866;,
  0.441064;0.059866;,
  0.449483;0.059866;,
  0.457903;0.059866;,
  0.466322;0.059866;,
  0.474742;0.059866;,
  0.483161;0.059866;,
  0.491581;0.059866;,
  0.500000;0.059866;,
  0.508420;0.059866;,
  0.516839;0.059866;,
  0.525258;0.059866;,
  0.533678;0.059866;,
  0.542097;0.059866;,
  0.550517;0.059866;,
  0.558936;0.059866;,
  0.567356;0.059866;,
  0.575775;0.059866;,
  0.584195;0.059866;,
  0.420015;0.211416;,
  0.428435;0.211416;,
  0.436854;0.211416;,
  0.445274;0.211416;,
  0.453693;0.211416;,
  0.462112;0.211416;,
  0.470532;0.211416;,
  0.478951;0.211416;,
  0.487371;0.211416;,
  0.495790;0.211416;,
  0.504210;0.211416;,
  0.512629;0.211416;,
  0.521049;0.211416;,
  0.529468;0.211416;,
  0.537888;0.211416;,
  0.546307;0.211416;,
  0.554727;0.211416;,
  0.563146;0.211416;,
  0.571566;0.211416;,
  0.579985;0.211416;,
  0.420015;0.043027;,
  0.428435;0.043027;,
  0.436854;0.043027;,
  0.445274;0.043027;,
  0.453693;0.043027;,
  0.462112;0.043027;,
  0.470532;0.043027;,
  0.478951;0.043027;,
  0.487371;0.043027;,
  0.495790;0.043027;,
  0.504210;0.043027;,
  0.512629;0.043027;,
  0.521049;0.043027;,
  0.529468;0.043027;,
  0.537888;0.043027;,
  0.546307;0.043027;,
  0.554727;0.043027;,
  0.563146;0.043027;,
  0.571566;0.043027;,
  0.579985;0.043027;,
  0.415805;0.194577;,
  0.424225;0.194577;,
  0.424225;0.160900;,
  0.415805;0.160900;,
  0.432644;0.194577;,
  0.432644;0.160900;,
  0.441064;0.194577;,
  0.441064;0.160900;,
  0.449483;0.194577;,
  0.449483;0.160900;,
  0.457903;0.194577;,
  0.457903;0.160900;,
  0.466322;0.194577;,
  0.466322;0.160900;,
  0.474742;0.194577;,
  0.474742;0.160900;,
  0.483161;0.194577;,
  0.483161;0.160900;,
  0.491581;0.194577;,
  0.491581;0.160900;,
  0.500000;0.194577;,
  0.500000;0.160900;,
  0.508420;0.194577;,
  0.508420;0.160900;,
  0.516839;0.194577;,
  0.516839;0.160900;,
  0.525258;0.194577;,
  0.525258;0.160900;,
  0.533678;0.194577;,
  0.533678;0.160900;,
  0.542097;0.194577;,
  0.542097;0.160900;,
  0.550517;0.194577;,
  0.550517;0.160900;,
  0.558936;0.194577;,
  0.558936;0.160900;,
  0.567356;0.194577;,
  0.567356;0.160900;,
  0.575775;0.194577;,
  0.575775;0.160900;,
  0.584195;0.194577;,
  0.584195;0.160900;,
  0.424225;0.127222;,
  0.415805;0.127222;,
  0.432644;0.127222;,
  0.441064;0.127222;,
  0.449483;0.127222;,
  0.457903;0.127222;,
  0.466322;0.127222;,
  0.474742;0.127222;,
  0.483161;0.127222;,
  0.491581;0.127222;,
  0.500000;0.127222;,
  0.508420;0.127222;,
  0.516839;0.127222;,
  0.525258;0.127222;,
  0.533678;0.127222;,
  0.542097;0.127222;,
  0.550517;0.127222;,
  0.558936;0.127222;,
  0.567356;0.127222;,
  0.575775;0.127222;,
  0.584195;0.127222;,
  0.424225;0.110383;,
  0.415805;0.110383;,
  0.432644;0.110383;,
  0.441064;0.110383;,
  0.449483;0.110383;,
  0.457903;0.110383;,
  0.466322;0.110383;,
  0.474742;0.110383;,
  0.483161;0.110383;,
  0.491581;0.110383;,
  0.500000;0.110383;,
  0.508420;0.110383;,
  0.516839;0.110383;,
  0.525258;0.110383;,
  0.533678;0.110383;,
  0.542097;0.110383;,
  0.550517;0.110383;,
  0.558936;0.110383;,
  0.567356;0.110383;,
  0.575775;0.110383;,
  0.584195;0.110383;,
  0.424225;0.059866;,
  0.415805;0.059866;,
  0.432644;0.059866;,
  0.441064;0.059866;,
  0.449483;0.059866;,
  0.457903;0.059866;,
  0.466322;0.059866;,
  0.474742;0.059866;,
  0.483161;0.059866;,
  0.491581;0.059866;,
  0.500000;0.059866;,
  0.508420;0.059866;,
  0.516839;0.059866;,
  0.525258;0.059866;,
  0.533678;0.059866;,
  0.542097;0.059866;,
  0.550517;0.059866;,
  0.558936;0.059866;,
  0.567356;0.059866;,
  0.575775;0.059866;,
  0.584195;0.059866;,
  0.420015;0.211416;,
  0.428435;0.211416;,
  0.436854;0.211416;,
  0.445274;0.211416;,
  0.453693;0.211416;,
  0.462112;0.211416;,
  0.470532;0.211416;,
  0.478951;0.211416;,
  0.487371;0.211416;,
  0.495790;0.211416;,
  0.504210;0.211416;,
  0.512629;0.211416;,
  0.521049;0.211416;,
  0.529468;0.211416;,
  0.537888;0.211416;,
  0.546307;0.211416;,
  0.554727;0.211416;,
  0.563146;0.211416;,
  0.571566;0.211416;,
  0.579985;0.211416;,
  0.420015;0.043027;,
  0.428435;0.043027;,
  0.436854;0.043027;,
  0.445274;0.043027;,
  0.453693;0.043027;,
  0.462112;0.043027;,
  0.470532;0.043027;,
  0.478951;0.043027;,
  0.487371;0.043027;,
  0.495790;0.043027;,
  0.504210;0.043027;,
  0.512629;0.043027;,
  0.521049;0.043027;,
  0.529468;0.043027;,
  0.537888;0.043027;,
  0.546307;0.043027;,
  0.554727;0.043027;,
  0.563146;0.043027;,
  0.571566;0.043027;,
  0.579985;0.043027;;
 }
}
