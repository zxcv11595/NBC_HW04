#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cassert>

#ifdef REQUIREMENTS
// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe
{
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients)
    {
    }
};


// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop
{
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const
    {
        if (recipes.empty())
        {
            std::cout << '\n';
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i)
        {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j)
            {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    // 검색한 물약 이름의 레시피 출력
    void searchRecipeByName(const std::string& name)
    {
        int count = 0;

        for (int i = 0; i < recipes.size(); ++i)
        {
            if (recipes[i].potionName == name)
            {
                std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
                std::cout << "  > 필요 재료: ";

                // 재료 목록을 순회하며 출력
                for (size_t j = 0; j < recipes[i].ingredients.size(); ++j)
                {
                    std::cout << recipes[i].ingredients[j];
                    // 마지막 재료가 아니면 쉼표로 구분
                    if (j < recipes[i].ingredients.size() - 1)
                    {
                        std::cout << ", ";
                    }
                }

                ++count;

                std::cout << std::endl;
            }
        }

        if (count == 0)
            std::cout << "존재하지 않는 물약입니다." << std::endl;
    }

    // 검색한 재료가 포함된 물약들 출력
    void searchRecipeByIngredient(const std::string& ingredient)
    {
        std::vector<PotionRecipe> tempRecipes;

        for (int i = 0; i < recipes.size(); ++i)
        {
            for (int j = 0; j < recipes[i].ingredients.size(); ++j)
            {
                if (recipes[i].ingredients[j] == ingredient)
                {
                    tempRecipes.push_back(PotionRecipe(recipes[i].potionName, recipes[i].ingredients));
                    break;
                }
            }
        }

        for (size_t i = 0; i < recipes.size(); ++i)
        {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j)
            {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    AlchemyWorkshop myWorkshop;

    while (true)
    {
        std::cout << std::endl;
        std::cout << "연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 물약 이름 검색" << std::endl;
        std::cout << "3. 재료 검색" << std::endl;
        std::cout << "4. 모든 레시피 출력" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true)
            {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝")
                {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty())
            {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else
            {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2)
        {
            std::string name = "";

            std::cout << "물약 입력: ";
            std::cin >> name;
            myWorkshop.searchRecipeByName(name);

        }
        else if (choice == 3)
        {
            std::string ingredient = "";

            std::cout << "재료 입력: ";
            std::cin >> ingredient;
            myWorkshop.searchRecipeByIngredient(ingredient);
        }
        else if (choice == 4)
        {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 5)
        {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else
        {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}
#endif

#ifdef CHALLENGE
// PotionRecipe class 정의
class PotionRecipe
{
public:
    // 멤버 변수들을 초기화하는 생성자
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : _name(name), _ingredients(ingredients)
    { }

    // 물약 이름을 반환
    const std::string& GetName() const
    {
        return _name;
    }

    // 물약을 만들기 위한 재료 목록을 반환
    const std::vector<std::string>& GetIngredients() const
    {
        return _ingredients;
    }

private:
    std::string _name;
    std::vector<std::string> _ingredients;
};

// RecipeManager class 정의
class RecipeManager
{
public:
    // 레시피 추가 후, 내부에 저장된 레시피의 포인터를 반환(없으면 nullptr)
    // - 예외처리 : 이미 있는 Recipe을 추가할 때, 자유롭게 처리
    PotionRecipe* AddRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    {
        for (int i = 0; i < _recipes.size(); ++i)
        {
            if (_recipes[i].GetName() == name)
            {
                std::cout << "이미 있는 레시피입니다." << std::endl;
                return &_recipes[i];
            }
        }

        _recipes.push_back(PotionRecipe(name, ingredients));
        return &_recipes.back();
    }

    // 이름으로 1개 찾기(없으면 nullptr)
    PotionRecipe* FindRecipeByName(const std::string& name)
    {
        for (int i = 0; i < _recipes.size(); ++i)
        {
            if (_recipes[i].GetName() == name)
            {
                return &_recipes[i];
            }
        }

        return nullptr;
    }

    // 재료로 여러 개 찾기(결과 복사본 반환)
    std::vector<PotionRecipe> FindRecipesByIngredient(const std::string& ingredient) const
    {
        std::vector<PotionRecipe> resultRecipes;

        for (int i = 0; i < _recipes.size(); ++i)
        {
            std::vector<std::string> ingredients = _recipes[i].GetIngredients();
            for (int j = 0; j < ingredients.size(); ++j)
            {
                if (ingredients[j] == ingredient)
                    resultRecipes.push_back(PotionRecipe(_recipes[i].GetName(), ingredients));
            }
        }

        return resultRecipes;
    }

    // 전체 레시피(읽기 전용 참조)
    const std::vector<PotionRecipe>& GetAllRecipes() const
    {
        return _recipes;
    }

private:
    std::vector<PotionRecipe> _recipes;
};

// StockManager class 정의
class StockManager
{
public:
    static constexpr int MAX_STOCK = 3;

    // 레시피 추가 시 자동으로 3개 재고 세팅
    void InitializeStock(const std::string& potionName)
    {
        _potionStock[potionName] = MAX_STOCK;
    }

    // 재고가 1개 이상이면 1개 지급(감소)하고 true, 아니면 false
    bool DispensePotion(const std::string& potionName)
    {
        if(GetStock(potionName))
            return _potionStock.at(potionName)--;
    }

    // 공병 반환(재고 +1).
    // - 예외처리 : 단, MAX_STOCK 초과 불가
    void ReturnPotion(const std::string& potionName)
    {
        assert(_potionStock.at(potionName) < MAX_STOCK);
        ++_potionStock.at(potionName);
    }

    // 현재 재고 조회(없으면 0)
    int GetStock(const std::string& potionName) const
    {
        auto it = _potionStock.find(potionName);

        if (it != _potionStock.end())
            return it->second;

        return 0;
    }


private:
    std::map<std::string, int> _potionStock;
};

// AlchemyWorkshop class 정의
class AlchemyWorkshop
{
public:
    // 레시피 추가 + 자동 재고 3개 생성
    // (중복 이름 처리 방식은 구현 자유: 덮어쓰기/거부/중복허용 등)
    void AddRecipe(const std::string& potionName, const std::vector<std::string>& ingredients)
    {
        _recipeManager.AddRecipe(potionName, ingredients);
        _stockManager.InitializeStock(potionName);
    }

    // 레시피/재고 출력(형식은 자유)
    void DisplayAllRecipes() const
    {
        int recipeSize = _recipeManager.GetAllRecipes().size();

        if (recipeSize == 0)
        {
            std::cout << '\n';
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipeSize; ++i)
        {
            std::cout << "- 물약 이름: " << _recipeManager.GetAllRecipes()[i].GetName() << ", 재고: "
                << _stockManager.GetStock(_recipeManager.GetAllRecipes()[i].GetName()) << std::endl;
            std::cout << "  > 필요 재료: ";

            int ingredientsSize = _recipeManager.GetAllRecipes()[i].GetIngredients().size();
            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < ingredientsSize; ++j)
            {
                std::cout << _recipeManager.GetAllRecipes()[i].GetIngredients()[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < ingredientsSize - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }

    // 재고 조회 (이름)
    int GetStockByName(const std::string& potionName) const
    {
        return _stockManager.GetStock(potionName);
    }

    // potionName으로 검색하여 재고 있으면 지급처리하고 true, 재고 없으면 false
    bool DispensePotionByName(const std::string& potionName)
    {
        return _stockManager.DispensePotion(potionName);
    }

    // 해당 재료를 포함하는 레시피들 중, 재고 있는 것들을 지급처리
    // 반환: 실제로 지급된 물약 이름 목록(없으면 빈 벡터)
    std::vector<std::string> DispensePotionsByIngredient(const std::string& ingredient)
    {
        std::vector<std::string> potionNameList;

        int recipeSize = _recipeManager.GetAllRecipes().size();
        for (int i = 0; i < recipeSize; ++i)
        {
            int ingredientsSize = _recipeManager.GetAllRecipes()[i].GetIngredients().size();
            for (int j = 0; j < ingredientsSize; ++j)
            {
                std::string potionName = _recipeManager.GetAllRecipes()[i].GetName();
                if (_recipeManager.GetAllRecipes()[i].GetIngredients()[j] == ingredient
                    && _stockManager.GetStock(potionName) > 0)
                {
                    DispensePotionByName(_recipeManager.GetAllRecipes()[i].GetName());
                    potionNameList.push_back(_recipeManager.GetAllRecipes()[i].GetName());
                }
            }
        }

        return potionNameList;
    }

    // potionName에 공병을 반환 처리(최대 3개 제한)
    void ReturnPotionByName(const std::string& potionName)
    {
        _stockManager.ReturnPotion(potionName);
    }

private:
    RecipeManager _recipeManager;
    StockManager _stockManager;
};

void main()
{
    AlchemyWorkshop workshop;

    workshop.AddRecipe("Healing Potion", { "Herb", "Water" });
    workshop.AddRecipe("Mana Potion", { "Magic Water", "Crystal" });
    workshop.AddRecipe("Stamina Potion", { "Herb", "Berry" });
    workshop.AddRecipe("Fire Resistance Potion", { "Fire Flower", "Ash" });

    std::cout << "=== 초기 상태 (레시피 추가 + 재고 자동 3개) ===\n";
    workshop.DisplayAllRecipes();

    std::cout << "\n[재고 확인] Healing Potion 재고: "
        << workshop.GetStockByName("Healing Potion") << "\n";

    std::cout << "\n=== 이름으로 지급 테스트 (Healing Potion 3회 지급) ===\n";
    std::cout << "1회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
    std::cout << "2회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
    std::cout << "3회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";

    std::cout << "현재 재고: " << workshop.GetStockByName("Healing Potion") << "\n";

    std::cout << "4회 지급(재고 없으면 실패): "
        << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";

    std::cout << "\n=== 재료로 지급 테스트 (ingredient = Herb) ===\n";
    std::vector<std::string> dispensed = workshop.DispensePotionsByIngredient("Herb");

    std::cout << "지급된 물약 수: " << dispensed.size() << "\n";
    for (const std::string& name : dispensed)
        std::cout << "- " << name << "\n";

    workshop.DisplayAllRecipes();

    std::cout << "\n=== 공병 반환 테스트 (Healing Potion) ===\n";
    workshop.ReturnPotionByName("Healing Potion");
    workshop.ReturnPotionByName("Healing Potion");
    workshop.ReturnPotionByName("Healing Potion"); // 이미 3이면 더 올라가면 안 됨

    std::cout << "반환 후 재고(최대 3 유지): "
        << workshop.GetStockByName("Healing Potion") << "\n";

    std::cout << "\n=== 최종 상태 ===\n";
    workshop.DisplayAllRecipes();
}
#endif