//
// Created by kitaS24 on 24.08.2025.
//

class TextSplit{
    std::string Text;
    char Divider = 0;
public:
    void SetStr(std::string Str){
        Text = Str;
    }
    void SetDivider(char C){
        Divider = C;
    }
    std::string GetText(unsigned int p){
        unsigned int InnerP = 0;
        std::string o = "";
        for (int i = 0; i < Text.length(); ++i) {
            if(Text.at(i) == Divider){

                if(InnerP == p){
                    return o;
                }
                InnerP = InnerP+1;
                o="";
            }else{
                o.append(1,Text.at(i));
            }
        }
        return o;
    }

    //returns if out of bounds
    bool GetTextOOB(unsigned int p){
        unsigned int InnerP = 0;
        std::string o = "";
        for (int i = 0; i < Text.length(); ++i) {
            if(Text.at(i) == Divider){

                if(InnerP == p){
                    return false;
                }
                InnerP = InnerP+1;
                o="";
            }else{
                o.append(1,Text.at(i));
            }
        }
        if(InnerP == p){
            return false;
        }
        return true;
    }
};