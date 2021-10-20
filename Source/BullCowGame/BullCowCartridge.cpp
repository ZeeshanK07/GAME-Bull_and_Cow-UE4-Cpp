#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    InitGame();
    PrintLine(TEXT("   Click: Mouse, next TAB and play!\n"));
}
void UBullCowCartridge::InitGame()
{
    HiddenWord = GetValidWords(Words)[FMath::RandRange(0, GetValidWords(Words).Num() - 1)];
    Lives = HiddenWord.Len() + 1;
    bGameOver = false;
    Introduction();
}
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}
void UBullCowCartridge::Introduction()
{
    PrintLine(TEXT("      Hej! Welcome in Bull & Cow!"));
    PrintLine(TEXT("   The rules of the game are simple.\n"));
    PrintLine(FString::Printf(TEXT(
        "1. You must write %i letters word for win!\n"
        "2. If You will write 1 good letter:\n"
        "   In good site = +1 Bull and -1 live.\n"
        "   In bad site = +1 Cow and -1 live.\n"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord));
}
void UBullCowCartridge::OnInput(const FString& PlayerInput)
{
    ProcessGuess(PlayerInput);
    EndGame(PlayerInput);
}
void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (HiddenWord == Guess)
        {
            bGameOver = true;
            GameStatus = "Player win";
            return;
        }
    else
    {
        --Lives;
        if (!IsIsogram(Guess))
            {
            PrintLine(TEXT("Not found any repeating letters,\n"
                "with hidden word."));
            }
        else
            {
            PrintLine(FString::Printf(TEXT("You have %i bull."), Lives));
            }
        if (HiddenWord.Len() != Guess.Len())
        {
            PrintLine(FString::Printf(TEXT("You must write %i letters word!"), HiddenWord.Len()));
        }
        if (Lives > 0)
        {
            PrintLine(FString::Printf(TEXT("It's not good.\n"
                "Now You have %i lives.\n"), Lives));
            return;
        }
        if (Lives <= 0)
        {
            bGameOver = true;
            GameStatus = "Player lost";
        }
    }
}
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0 ; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                //Bull = Bull + 1;
                return false;
            }
        }
    }
    return true;
}
void UBullCowCartridge::EndGame(const FString& Guess)
{
    if (bGameOver)
    {
        if (GameStatus == "Player lost")
        {
            ClearScreen();
            PrintLine(FString::Printf(TEXT("You have not any life so You lose.\n"
                "The hidden word was: %s."), *HiddenWord));
            PrintLine(TEXT("\n\n"
                "If You want play again write Yes\n"
                "If You don't want play again click ESC"));
            if (Guess == "Yes")
            {
                ClearScreen();
                bGameOver = false;
                InitGame();
            }
        }
        if (GameStatus == "Player win")
        {
            ClearScreen();
            PrintLine(TEXT("Congratulations!!, YOU WIN!"));
            PrintLine(TEXT("\n\n"
                "If You want play again write Yes\n"
                "If You don't want play again click ESC"));
            if (Guess == "Yes")
            {
                ClearScreen();
                bGameOver = false;
                InitGame();
            }
        }
    }
}
