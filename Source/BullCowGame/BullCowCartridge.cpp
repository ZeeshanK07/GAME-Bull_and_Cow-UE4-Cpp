#include "BullCowCartridge.h"

// GAME - START
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame(); //Fuction of init game
    PrintLine(TEXT("   Click: Mouse, next TAB and play!\n"));
}
void UBullCowCartridge::InitGame()
{
    HiddenWord = TEXT("cola");
    Lives = HiddenWord.Len() + 1;
    Bull = 0;
    Cow = 0;
    bGameOver = false;
    Introduction();
}
void UBullCowCartridge::Introduction()
{
    PrintLine(TEXT("      Hej! Welcome in Bull & Cow!")); // Introduction part
    PrintLine(TEXT("   The rules of the game are simple.\n"));
    PrintLine(FString::Printf(TEXT(
        "1. You must write %i letters word for win!\n"
        "2. If You will write 1 good letter:\n"
        "   In good site = +1 Bull and -1 live.\n"
        "   In bad site = +1 Cow and -1 live.\n"), HiddenWord.Len())); // Introduction start
}
// GAME - LOGIC
void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ProcessGuess(Input);
    EndGame(Input);
}
void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (HiddenWord == Guess) // Player Win
    {
        bGameOver = true;
        GameStatus = "Player win";
        return;
    }
    else
    {
        Lives = --Lives; // Remove 1 live
        if (HiddenWord.Len() != Guess.Len()) // Word is too long or too short
        {
            PrintLine(FString::Printf(TEXT("You must write %i letters word!"), HiddenWord.Len()));
        }
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("Not found any repeating letters,\n"
                "with hidden word."));
            return;
        }
        /*if (IsIsogram(Guess))
        {
            PrintLine(FString::Printf(TEXT("You have %i bull."), Bull));
        }*/
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
bool UBullCowCartridge::IsIsogram(FString Word) const
{
    //int i = 0;
    //TCHAR Guess[];
    // HiddenWord[0]; HiddenWord[0 < HiddenWord.Len() - 1]; ++HiddenWord[0]

    /*for (HiddenWord[i]; HiddenWord[i < HiddenWord.Len() - 1]; ++HiddenWord[i])
        {
            if (Guess[i] == HiddenWord[i])
            {
                ++Bull; // add +1 bull = letter is in god site
            }
        }*/
    return true;
}
void UBullCowCartridge::EndGame(FString Guess)
{
    if (bGameOver) // Game over
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
            PrintLine(TEXT("Good, YOU WIN!")); // Win
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