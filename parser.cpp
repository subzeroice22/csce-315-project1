/* parse.c: simple parser -- no output
 * grammar:
 *  expression = ["+"|"-"] term {("+"|"-”) term} .
 *	term = factor {("*"|"/”) factor}
 *	factor = ident | number | "(" expression ")”'
 * Motivation & more examples at: http://www.cs.utsa.edu/~wagner/CS3723/rdparse/rdparser.html, http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
 * See txt file for some sample runs.
 * 
 * This program is to demonstrate recursive descent parsing. It expects input
 * expressions at > followed by DOT(.). Look at slides (pg 7) for grammar. Exit
 * safely with Ctrl-C. In case input expression does not meet grammar, the
 * program generates Error and exits. 
 * Feel free to point out errors if any (and fixes!) to 
 * aalap[AT]cse[DOT]tamu[DOT]edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
//#include <deque>
#include <vector>
#include<boost/tokenizer.hpp>

using namespace std;

class Parser{
private:
	vector<string> sTokens; //ScannerTokens  i.e. [dog] [<] [-] ... ["] [joe] [bob] ... [;]
	vector<string> pTokens; //Completed Parser Tokens i.e. [dog] [<-] ... ["] [joe bob] ["] ... [;]  //perhaps no special chars like [<-] and ["] ?
	int sTokI;
	string sTok;
	
	string tok; //TODO: kill off
	int level;
	
	
	void getSTok(){
		sTokI++;
		sTok = sTokens[sTokI];
	}
	
public:
	Parser(){
		level=0;
	}
	Parser(string fileName){
		level=0;
		ifstream inFile( fileName.c_str() );
		//Need to put in loop, splitting prog on '\n' or ';' , then handle each CorQ
		while(inFile.good() ){ //assuming infile will be newLine seperated
			string line;
			getline(inFile, line);	//function in/of <string> lib
			if(line==""){continue;} //Skip blank Lines
			cout<<"******************************\n**Handling Line: "<<line<<endl;
			//Get Tokens
			vector<string> toks = tokenizeLine(line);
			//Print Tokens
			cout<<"**Tokens: ";
			for(vector<string>::iterator it=toks.begin(); it!=toks.end(); ++it){
				cout<<"["<<(*it)<<"] ";
			}cout<<endl;
			
			//Parse
			if(isCommand(toks[0])){
				cout<<"Need To implement Command Parsing.. Skipping\n";
			}else{
				sTokens = toks;
				sTokI = 0;
				sTok= sTokens[0];
				ParseQuery();
			}
						
			cout<<"\n**Done handling line\n****************************\n\n";
			cout << "Press ENTER to continue";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	
	vector<string> tokenizeLine(string line){
		vector<string> tokens;
		boost::char_separator<char> separator(" \n","\"()+<>=-;,");
		boost::tokenizer< boost::char_separator<char> > tok( (std::string::const_iterator)line.begin(), (std::string::const_iterator)line.end(), separator);
		for(boost::tokenizer< boost::char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end(); ++beg){
		   tokens.push_back( *beg );
		}
		return tokens;
	}
	
	void lex(vector<string> tokens){
		while(1){
			;
		}		
	}
	
	bool isCommand(string fWord){
		if(fWord=="OPEN"){
		
		}else if(fWord=="CLOSE"){
		
		}else if(fWord=="WRITE"){
		
		}else if(fWord=="EXIT"){
		
		}else if(fWord=="SHOW"){

		}else if(fWord=="CREATE"){

		}else if(fWord=="UPDATE"){
		
		}else if(fWord=="INSERT"){
		
		}else if(fWord=="DELETE" ){
		
		}else{
			return false;
		}
		return true;
	}
	
	/*Old Funcs
	void handleProgram(string prog){
		cout<<"*******\nSOMEONE CALLED handleProgram\n********\n";
	
		vector<string> Lines;
		stringstream iss(prog);
		
		string ln="";
		while(iss.good()){
			char c;
			iss>>c;
			ln+=c;
			if(c==';'){
				Lines.push_back(ln);
				cout<<"added line: "<<ln<<endl;
				ln="";
			}
		}
			// cout<<"read line# "<<i<<endl;
			
			// int maxLineSize=1020;
			// char buff[maxLineSize];
			// string ln;
			
			// iss.get(buff,maxLineSize,';');
			// getline(iss, ln, ':');
			// cout<<"read:"<<iss.gcount()<<" chars"<<endl;
			
			// string newLn(buff);
			// cout<<"adding newLine: "<<ln<<endl;
			// Lines.push_back(ln);
				
			//cout<<"done breaking apart program..."<<endl;
		
		for(vector<string>::iterator it=Lines.begin(); it!=Lines.end(); ++it){
			cout<<"calling handle CorQ on string: "<<(*it)<<endl;
			//handleCorQ(*it);
		}
		
	}
	
	bool handleQuery(string Query){
		cout<<"Handeling a query!!!!!\n"<<Query<<endl;
		return true;
	}
		
	bool handleCommand(string Cmd){
		stringstream iss(Cmd);
		string fWord;
		iss>>fWord;
		if(fWord=="OPEN"){
		
		}else if(fWord=="CLOSE"){
		
		}else if(fWord=="WRITE"){
		
		}else if(fWord=="EXIT"){
		
		}else if(fWord=="SHOW"){

		}else if(fWord=="CREATE"){

		}else if(fWord=="UPDATE"){
		
		}else if(fWord=="INSERT"){
		
		}else if(fWord=="DELETE" ){
		
		}else{
			return false;
		}
		return true;
	}
	*/
	
private:	
	/*Non-terminal Functions:
	void query(); void relationName(); void identifier(); void alpha(); void digit(); void expr(); void atomicExpr(); void selection();
	void condition(); void conjunction(); void comparison(); void op(); void operand(); void attributeName(); void literal(); 
	void projection(); void attributeList(); void renaming(); void unionF(); void difference(); void product();  
	*/
	/*Non-terminal helpers:
	bool isDigit(string);
	bool isAlpha(string);
	*/
	/*Parser Specific Functions/Members:
	void getToke();
	Helper Funcs
	*/

	//Helper Funcs
	bool isDigit(string a){return true;}
	bool isAlpha(string a){return true;}
	void errorS(string s) {
	   cout<<"\n*** ERROR: "<<s<<endl;;
	   exit(1);
	}
	void enter(string name) {
		spaces(level++);
		cout<<"+-"<<name<<": Enter, \t";
		cout<<"Tok == "<<sTok<<endl;
		//printf("+-%c: Enter, \t", name);
		//printf("Sym == %s\n", sym);
	}
	void leave(string name) {
		spaces(--level);
		cout<<"+-"<<name<<": Leave, \t";
		cout<<"Tok == "<<tok<<endl;
		//printf("+-%c: Leave, \t", name);
		//printf("Sym == %c\n", sym);
	}
	void spaces(int local_level) {
		while (local_level-- > 0)
			cout<<"| ";
	}
	void getToke(){ //TODO: fix this repetition
		getSTok();
	}

	void ParseQuery(){
		query();
	}
	
	//query ::= relation-name <- expr ;
	void query(){
		enter("Query");
		relationName();
		if(tok == "<-"){
			getSTok();
			expr();
		}else errorS("Expected \"<-\"");
		leave("Query");
	}

	//relation-name ::= identifier
	void relationName(){
		enter("RelationName");
		identifier();
	}

	//identifier ::= alpha { ( alpha | digit ) }
	void identifier(){
		enter("Idenfitier");
		string identif = sTok;
		
		for(int i=0; i<identif.size(); i++)
		alpha();
		
		while(isDigit(tok) || isAlpha(tok) ) {
			if(isDigit(tok)){
				digit();
			}else{
				alpha();
			}
		}
	}

	//alpha ::= a | … | z | A | … | Z | _
	void alpha(){

	}
	
	//alpha ::= a | … | z | A | … | Z | _
	bool isAlpha(char c){
		
	}
	
	//digit ::= 0 | … | 9
	bool isDigit(char c){
		
	}
	

	//digit ::= 0 | … | 9
	void digit(){

	}
	/* bool isDigit(Token t){
		try{
			int dig = atoi(t); 
			if(dig<10 && dig>=0){
				return true;	
			}
		}
		catch(e){ return false; }
		return false;
	}
	*/

	//expr ::= atomic-expr | selection | projection | renaming | union | difference | product
	void expr() {
		enter("Expression");
		atomicExpr();//...
	}

	//atomic-expr ::= relation-name | ( expr )
	void atomicExpr(){
		if(tok=="("){
			getToke();
			expr();
			if(tok!=")"){
				errorS("expected closing paren");
			}
			getToke();
		}else{
			relationName();
		}
	}

	//selection ::= select ( condition ) atomic-expr
	void selection(){

	}

	//condition ::= conjunction { || conjunction }
	void condition(){
		enter("Condition");
		conjunction();
		if(tok == "||"){
			getToke();
			conjunction();
		}
		leave("Condition");
	}

	//conjunction ::= comparison { && comparison }
	void conjunction(){
		enter("Conjunction");
		comparison();
		while(tok=="&&"){
			getToke();
			comparison();
		}
		leave("Conjuction");
	}

	//comparison ::= operand op operand | ( condition )
	void comparison(){
		/* Old
		enter("Comparison");
		Operand();
		Op();
		Operand();
		if(sym=="|"){
			getsym();
			Condition();
		}
		leave("Comparison");
		*/
		enter("Comparison");
		if(tok=="("){
			getToke();//clear "("
			condition();
			if(tok!=")"){
				errorS("expected closing paren"); 
			}
			getToke();//clear ")"
		}else{
			operand();
			op();
			operand();
		}
		leave("Comparison");
	}

	//enum opEnum {"=="=0, "!=", "<" , ">", "<=", ">="}
	void op(){
		if(tok == "=="){
		
		}else if(tok == "!="){
		
		}else if(tok == "<"){
		
		}else if(tok == ">"){
		
		}else if(tok == "<="){
		
		}else if(tok == ">="){
		
		}else{
			//Not an 'op'
		}
	}

	//operand ::= attribute-name | literal
	void operand(){

	}

	// attribute-name ::= identifier
	void attributeName(){
		enter("attributeName");
		identifier();
		leave("attributeName");
	}

	// literal ::= intentionally left unspecified
	void literal(){
		//... require futher clarification
	}

	// projection ::= project ( attribute-list ) atomic-expr
	void projection(){
		enter("Projection");
		if(tok=="project"){
		
			while(tok == "(" ){
				getToke(); //clear "("
				attributeList();
				if(tok != ")" ){
					errorS("Expected closing paren");
				} getToke(); //clear ")"
			}		
			atomicExpr();
			leave("Projection");
		}
	}

	// attribute-list ::= attribute-name { , attribute-name } 
	void attributeList(){
		enter("AttributeList");
		attributeName();
		while(tok==","){
			getToke();
			attributeName();
		}
		leave("AttributeList");
	}

	// renaming ::= rename ( attribute-list ) atomic-expr
	void renaming(){
		enter("Renaming");
		if(tok == "rename"){
			while(tok == "(" ){
				getToke(); //clear "("
				attributeList();
				if(tok != ")" ){
					errorS("Expected closing paren");
				} getToke(); //clear ")"
			}
			atomicExpr();
		}
		leave("Renaming");
	}

	// union ::= atomic-expr + atomic-expr
	void unionF(){
		enter("Union");
		atomicExpr();
		if(tok == "+" ){
			getToke(); //clear "+"
		}else{ errorS("Expected +"); }
		atomicExpr();
		leave("Union");
	}

	// difference ::= atomic-expr - atomic-expr
	void difference(){
		enter("Difference");
		atomicExpr();
		if(tok == "-" ){
			getToke(); //clear "-"
		}else{ errorS("Expected -"); }
		atomicExpr();
		leave("Difference");
	}

	// product ::= atomic-expr * atomic-expr 
	void product(){
		enter("Product");
		atomicExpr();
		if(tok == "*" ){
			getToke(); //clear "*"
		}else{ errorS("Expected *"); }
		atomicExpr();
		leave("Product");
	}
	
};

int main() {
	cout<<"-Starting Parser Main\n";
	Parser* myP = new Parser("parser_milestone_good_inputs.txt");
	cout<<"-Exiting Parser Main\n";
	
	return 0;
}
