#include<iostream>
#include<string>
#include<vector>

int SplitSize(const std::string& strString, char cDelimiter){
	int istrLen = strString.length(), iIt = 0, iCount = 0;
	for(; iIt<istrLen; iIt++){
		while(strString[iIt] != cDelimiter && strString[iIt] != '\0'){
			iIt++;
		}
		iCount++;
	}
	return iCount;
}

void strSplit(const std::string& strString, char cDelimiter, std::vector<std::string>& vcOut, int iMax){
	if(vcOut.size() > 0){
		vcOut.erase(vcOut.begin(), vcOut.end());
	}
	int istrLen = strString.length(), iIt = 0, iCounter = 0, iTmp = 0;
	for(; iIt<istrLen; iIt++){
		std::string strTmp = "";
		while(strString[iIt] != cDelimiter && strString[iIt] != '\0'){
			strTmp.append(1, strString[iIt++]);
			iCounter++;
		}
		iCounter = 0;
		vcOut.push_back(strTmp);
		if(++iTmp == iMax){ break; }
		
	}
}

void PrintTable(std::vector<std::string>& vHeaders, std::vector<std::string>& vLines, const char cSplitChar){
	char cTmp[4];
	cTmp[0] = cSplitChar;
	cTmp[1] = '-';
	cTmp[2] = '-';
	cTmp[3] = '\0';
	int iMaxSize = 0, iHead = vHeaders.size(), iLine = vLines.size(), iIt = 0, iIt2 = 0, iTmp = 0, iTmp2 = 0;
	std::vector<std::string> vcTmp;
	for(; iIt<iLine; iIt++){
		iTmp = SplitSize(vLines[iIt], cSplitChar);
		iMaxSize = iTmp > iMaxSize ? iTmp : iMaxSize;
		iMaxSize = iHead > iMaxSize ? iHead : iMaxSize;
	}
	for(iIt=iHead; iIt<iMaxSize; iIt++){
		vHeaders.push_back("--");
	}
	for(iIt=0; iIt<iLine; iIt++){
		iTmp = SplitSize(vLines[iIt], cSplitChar);
		while(iTmp++ < iMaxSize){
			vLines[iIt].append(cTmp);
		}
	}
	int iFieldsSize[100][100];
	int iFields[100];
	for(iIt=0; iIt<iMaxSize; iIt++){
		iFields[iIt] = 0;
		iFieldsSize[0][iIt] = vHeaders[iIt].length();
	}
	for(iIt=1, iIt2 = 0; iIt2<iLine; iIt++, iIt2++){
		strSplit(vLines[iIt2], cSplitChar, vcTmp, 100);
		iTmp = vcTmp.size();
		for(iTmp2=0; iTmp2<iTmp; iTmp2++){
			iFieldsSize[iIt][iTmp2] = int(vcTmp[iTmp2].length()); 
		}
		while(iTmp2<iMaxSize){
			iFieldsSize[iIt][iTmp2++] = 2; //default --
		}
	}
	for(iIt=0; iIt<iLine+1; iIt++){
		for(iIt2=0; iIt2<iMaxSize; iIt2++){
			iFields[iIt2] = iFieldsSize[iIt][iIt2] > iFields[iIt2] ? iFieldsSize[iIt][iIt2] : iFields[iIt2];
		}
	}
	std::string strPadding = "", strSolidBorder = " *", strCutBorder = " .";
	for(iIt=0; iIt<int(vHeaders.size()); iIt++){
		strSolidBorder.append(iFields[iIt] + 3, '=');
		strCutBorder.append(iFields[iIt] + 3, '-');
	}
	strSolidBorder.pop_back();
	strCutBorder.pop_back();
	strSolidBorder.append(1, '*');
	strCutBorder.append(1, '.');
	std::cout<<strSolidBorder<<"\n | ";
	
	
	for(iIt=0; iIt<int(vHeaders.size()); iIt++){
		strPadding.erase(strPadding.begin(), strPadding.end());
		iTmp = vHeaders[iIt].length();
		iTmp2 = iFields[iIt] > iTmp ? (iFields[iIt] - iTmp) : (iTmp -iFields[iIt]);
		strPadding.append(iTmp2, ' ');
		std::cout<<vHeaders[iIt]<<strPadding<<" | ";
	}
	std::cout<<"\n"<<strSolidBorder<<"\n";
	for(iIt=0; iIt<iLine; iIt++){
		std::cout<<" | ";
		strSplit(vLines[iIt], cSplitChar, vcTmp, 100);
		for(iIt2=0; iIt2<int(vcTmp.size()); iIt2++){
			strPadding.erase(strPadding.begin(), strPadding.end());
			iTmp = vcTmp[iIt2].length();
			iTmp2 = iFields[iIt2] > iTmp ? (iFields[iIt2] - iTmp) : (iTmp < iFields[iIt2]);
			strPadding.append(iTmp2, ' ');
			std::cout<<vcTmp[iIt2]<<strPadding<<" | ";
		}
		std::cout<<"\n"<<strSolidBorder<<"\n";
	}
}

void test1(){
	std::vector<std::string> head, fields;
	head.push_back("col1"); 
	head.push_back("colum id 2");
	head.push_back("col3");
	head.push_back("column4");
	head.push_back("col5");
	head.push_back("col6");
	fields.push_back("row1-1,row1-2,col1-3,col1-4");
	fields.push_back("row2-1,row2-2,row2-3,row2-4");
	fields.push_back("row3-1,row3-2,row3-3,row3-4,row3-5");
	fields.push_back("row4-1,row4-2,row4-3,row4-4");
	fields.push_back("row5-1,row5-2,row5-3,row5-4");
	PrintTable(head, fields, ',');
	std::cout<<"\n\n";
}

void test2(){
	std::vector<std::string> head, fields;
	head.push_back("col1"); 
	head.push_back("colum id 2");
	head.push_back("col3");
	head.push_back("column4");
	fields.push_back("row1-1,row1-2,col1-3,col1-4");
	fields.push_back("row2-1,row2-2,row2-3,row2-4");
	fields.push_back("row3-1,row3-2,row3-3,row3-4,row3-5");
	fields.push_back("row4-1,row4-2,row4-3,row4-4");
	fields.push_back("row5-1");
	PrintTable(head, fields, ',');
	std::cout<<"\n\n";
}

void test3(){
	std::vector<std::string> head, fields;
	head.push_back("1"); 
	head.push_back("colum id 2");
	head.push_back("c3");
	head.push_back("c4");
	fields.push_back("1,row1-2,c3,col1-4");
	fields.push_back("1,row2-3,c4");
	fields.push_back("1,row3-2,c3,row3-4,row3-5");
	fields.push_back("1,row4-2,43,row4-4");
	fields.push_back("5");
	PrintTable(head, fields, ',');
	std::cout<<"\n\n";
}

int main(){
	test1();
	test2();
	test3();
	return 0;
}
