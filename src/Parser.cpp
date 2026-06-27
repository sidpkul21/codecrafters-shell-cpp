#include "Parser.hpp"
#include <string>
#include <sstream>
#include <iostream>

namespace {

    enum class processMode {
        normal,
        singlequote,
        doublequote,
        escape,
    };

    typedef struct state{
        std::vector<std::string> tokens;
        std::string str;
        processMode mode = processMode::normal;
        bool isbuildingtoken = false;
    } state;

    void buildtoken(char c, state &ctx) {
        ctx.str += c;
        ctx.isbuildingtoken = true;
    }

    void finishtoken(state &ctx) {
        if(ctx.isbuildingtoken) {
            ctx.tokens.push_back(ctx.str);
            ctx.str.clear();
            ctx.isbuildingtoken = false;
        }
    }

    void processNormal(char c, state &ctx) {
        if(c == '"') {
            ctx.mode = processMode::doublequote;
            ctx.isbuildingtoken = true;
        } else if(c == '\'') {
            ctx.mode = processMode::singlequote;
            ctx.isbuildingtoken = true;
        } else if(c == '\\') {
            ctx.mode = processMode::escape;
            ctx.isbuildingtoken = true;
        } else if(std::isspace(static_cast<unsigned char>(c))) {
            finishtoken(ctx);
        } else {
            buildtoken(c, ctx);
        }            
    }

    void processSingleQuote(char c, state &ctx) {
        if(c == '\'') {
            ctx.mode = processMode::normal;
            ctx.isbuildingtoken = true;
        } else {
            buildtoken(c, ctx);
        }
    }

    void processDoubleQuote(char c, state &ctx) {
        if(c == '"') {
            ctx.mode = processMode::normal;
            ctx.isbuildingtoken = true;
        } else {
            buildtoken(c, ctx);
        }
    }

    void processEscape(char c, state &ctx) {
        buildtoken(c, ctx);
        ctx.mode = processMode::normal;
    }

    std::vector<std::string> tokenizer(const std::string& input) {
        state ctx;
        for(char c: input) {
            switch(ctx.mode) {
                case processMode::normal:
                    processNormal(c, ctx);
                    break;
                case processMode::singlequote:
                    processSingleQuote(c, ctx);
                    break;
                case processMode::doublequote:
                    processDoubleQuote(c, ctx);
                    break;
                case processMode::escape:
                    processEscape(c, ctx);
                    break;
            }
        }
        finishtoken(ctx);
        return ctx.tokens;
    }

}


Command Parser::parse(const std::string& input) const{
    Command command;
    command.input = input;
    
    auto tokens = tokenizer(input);
    
    if(tokens.empty()) {
        return command;
    }

    command.name = tokens[0];

    for(size_t i = 1; i < tokens.size(); i ++) {
        command.args.push_back(tokens[i]);
    }
    
    return command;
}