#include<stdio.h>
#include<vector>
#include<string>
#include<fstream>
#define COUNTOF(ARR)	(sizeof(ARR)/sizeof(*(ARR)))
bool load_txt(const char *filename, std::string &out)
{
	std::ifstream ifs(filename, std::ios::in);
	if(ifs.is_open())
	{
		out.assign(std::istreambuf_iterator<char>{ifs}, {});
		ifs.close();
		return true;
	}
	return false;
}
unsigned long long read_int(const char *text, size_t len, int &idx)
{
	unsigned long long ret=0;
	int base=0;
	if(text[idx]=='0')
	{
		++idx;
		if(idx>=len)
			return ret;
		char c=text[idx]&0xDF;
		if(c=='X')
			base=16, ++idx;
		else if(c=='B')
			base=2, ++idx;
		else
			base=8;
		if(idx>=len)
			return ret;
	}
	else
		base=10;
	for(;idx<len;++idx)
	{
		unsigned char c=text[idx]-'0';
		if(c<10)
		{
			ret*=base;
			ret+=c;
		}
		else
		{
			c=(text[idx]&0xDF)-'A';
			if(c>=6)
				break;
			ret*=base;
			ret+=10+c;
		}
	}
	return ret;
}
void skip_ws(const char *text, size_t len, int &k)
{
	for(;k<len&&isspace(text[k]);++k);
}
void skip_till_ws(const char *text, size_t len, int &k)
{
	for(;k<len&&!isspace(text[k]);++k);
}
void skip_till(const char *text, size_t len, int &idx, char delim)
{
	for(;idx<len&&text[idx]!=delim;++idx);
}
struct RegInfo
{
	size_t offset;
	std::string name, comment;
};
void parse_table(const char *text, size_t len, std::vector<RegInfo> &info)
{
	char delim=',';
	int idx=0;
	RegInfo temp;
	for(;idx<len;)
	{
		skip_ws(text, len, idx);
		temp.offset=read_int(text, len, idx);//read offset

		skip_till(text, len, idx, delim);
		if(text[idx]!=delim)
			break;
		++idx;

		skip_ws(text, len, idx);
		int start2=idx;
		skip_till(text, len, idx, delim);
		temp.name.assign(text+start2, text+idx);//read register name

		if(text[idx]!=delim)
			break;
		++idx;

		skip_ws(text, len, idx);
		start2=idx;
		skip_till(text, len, idx, '\n');
		temp.comment.assign(text+start2, text+idx);//read comment

		info.push_back(std::move(temp));
		idx+=text[idx]=='\n';
	}
}
const int regsize=4;
int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Usage:  bspgen filename\n");
		return 1;
	}
	std::string text;
	load_txt(argv[1], text);
	std::vector<RegInfo> info;
	parse_table(text.c_str(), text.size(), info);

	for(size_t k=0;k<info.size();++k)
	{
		auto &i=info[k];
		printf("0x%03lX, %s, %s\n", i.offset, i.name.c_str(), i.comment.c_str());
	}
	
	size_t max_offset=0;
	for(size_t kr=0;kr<info.size();++kr)//find address range
		if(max_offset<info[kr].offset)
			max_offset=info[kr].offset;
	max_offset+=regsize;

	std::vector<size_t> slots(max_offset/regsize, -1);
	for(size_t kr=0;kr<info.size();++kr)//assign struct slots
	{
		if(info[kr].offset%regsize)
		{
			printf("Register 0x%03lX %s is not aligned\n", info[kr].offset, info[kr].name.c_str());
			return 1;
		}
		slots[info[kr].offset/regsize]=kr;
	}
	
	std::string out="typedef struct RegisterMapStruct\n{";
	for(size_t ka=0, nreserved=0;ka<slots.size();)
	{
		if(slots[ka]!=-1)
		{
			auto &i=info[slots[ka]];
			out+="\n\tunsigned ";
			out+=i.name;
			out+=";\t//";
			out+=i.comment;
			++ka;
		}
		else
		{
			int count=ka;
			for(;ka<slots.size()&&slots[ka]==-1;++ka);
			count=ka-count;
			out+="\n\tunsigned reserved";
			out+=std::to_string(nreserved);
			if(count>1)
			{
				out+="[";
				out+=std::to_string(count);
				out+="]";
			}
			out+=";";
			++nreserved;
		}
	}
	out+="\n} RegisterMap;\n";

	printf("%s\n", out.c_str());
	
	return 0;
}
