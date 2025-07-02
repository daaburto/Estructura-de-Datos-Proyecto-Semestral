#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include "PatternSearchAlgorithm.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

class SuffixTree : public PatternSearchAlgorithm {
public:

    std::vector<int> search(const std::string& text, const std::string& pattern) override {
    	data = text;
        if (data.back() != '$') data.push_back('$');
        root = std::make_shared<Node>();
        buildNaive();
        return searchPattern(pattern);
    }


private:
    struct Node {
    	//los hijos del nodo es una lista de pares, los bordes del intervalo y el puntero al hijo en si
    	std::vector<std::pair< std::pair<int,int>, std::shared_ptr<Node> >> children;
    	//para las hojas, indice de inicio de sufijo
        int start = -1;
    };

    using NodePtr = std::shared_ptr<Node>;

    std::string data;
    NodePtr root;

    void buildNaive() {
        int n = data.size();
        for (int i = 0; i < n; ++i) {
            insert(root, i, n);
        }
    }
	void insert(std::shared_ptr<Node> node, int suffixStart, int n) {
	    int i = suffixStart;
	    while (i < n) {
	        bool found = false;
	        for (auto& child : node->children) {
	            int start = child.first.first;
	            int end = child.first.second;
	            int len = 0;

	            while (start + len < end && i + len < n && data[start + len] == data[i + len]) {
	                ++len;
	            }

	            if (len == 0) continue;

	            if (len < end - start) {
	                //calza parcialmente, crear nodo intermedio
	                auto mid = std::make_shared<Node>();
	                mid->children.push_back({{start + len, end}, child.second});
	                child.first.second = start + len;
	                child.second = mid;

	                auto leaf = std::make_shared<Node>();
	                leaf->start = suffixStart;
	                mid->children.push_back({{i + len, n}, leaf});
	                return;
	            }

	            //calza completamente, continuar para abajo
	            i += len;
	            node = child.second;
	            found = true;
	            break;
	        }

	        if (!found) {
	            auto leaf = std::make_shared<Node>();
	            leaf->start = suffixStart;
	            node->children.push_back({{i, n}, leaf});
	            return;
	        }
	    }
	}


    std::vector<int> collectStarts(std::shared_ptr<Node> node) const {
    	//busca todos los indices de inicio de las hojas hijas de el nodo
	    std::vector<int> res;
	    std::vector<std::shared_ptr<Node>> stack{node};

	    while (!stack.empty()) {
	        auto current = stack.back();
	        stack.pop_back();

	        if (current->start != -1) {
	            res.push_back(current->start);
	        }

	        for (const auto& child : current->children) {
	            stack.push_back(child.second);
	        }
	    }

	    std::sort(res.begin(), res.end());
	    return res;
	}


    std::vector<int> searchPattern(const std::string& pattern) const {
	    auto node = root;
	    int i = 0;

	    while (i < (int)pattern.size()) {
	        bool matched = false;

	        for (const auto& child : node->children) {
	            int start = child.first.first;
	            int end = child.first.second;
	            int j = 0;

	            while (start + j < end && i + j < (int)pattern.size() && data[start + j] == pattern[i + j]) {
	                ++j;
	            }

	            if (j == 0) continue;

	            if (i + j == (int)pattern.size()) {
	                //patron encontrado
	                return collectStarts(child.second);
	            }

	            if (j == end - start) {
	                //calza con toda la arista, continuar
	                i += j;
	                node = child.second;
	                matched = true;
	                break;
	            }
	            return {};
	        }

	        if (!matched) return {};
	    }

	    return collectStarts(node);
	}


	    std::string getName() const override {
	        return "Suffix Tree";
	    }
	};

#endif // SUFFIX_TREE_H
	