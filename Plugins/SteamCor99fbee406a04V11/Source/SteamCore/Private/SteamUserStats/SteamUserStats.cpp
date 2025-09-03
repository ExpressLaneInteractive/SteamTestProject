/**
* Copyright (C) 2017-2025 eelDev AB
*
* Official Steamworks Documentation: https://partner.steamgames.com/doc/api/ISteamUserStats
*/

#include "SteamUserStats/SteamUserStats.h"
#include "SteamUserStats/SteamUserStatsAsyncTasks.h"
#include "SteamCorePluginPrivatePCH.h"

void UUserStats::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

#if WITH_STEAMCORE
	OnUserAchievementIconFetchedCallback.Register(this, &UUserStats::OnUserAchievementIconFetched);
	OnUserStatsReceivedCallback.Register(this, &UUserStats::OnUserStatsReceived);
	OnUserStatsStoredCallback.Register(this, &UUserStats::OnUserStatsStored);
	OnUserAchievementStoredCallback.Register(this, &UUserStats::OnUserAchievementStored);
	OnUserStatsUnloadedCallback.Register(this, &UUserStats::OnUserStatsUnloaded);
	OnUserAchievementIconFetchedCallback.Register(this, &UUserStats::OnUserAchievementIconFetched);

	if (IsRunningDedicatedServer())
	{
		OnUserAchievementIconFetchedCallback.SetGameserverFlag();
		OnUserStatsReceivedCallback.SetGameserverFlag();
		OnUserStatsStoredCallback.SetGameserverFlag();
		OnUserAchievementStoredCallback.SetGameserverFlag();
		OnUserStatsUnloadedCallback.SetGameserverFlag();
		OnUserAchievementIconFetchedCallback.SetGameserverFlag();
	}
#endif
}

void UUserStats::Deinitialize()
{
#if WITH_STEAMCORE
	OnUserAchievementIconFetchedCallback.Unregister();
	OnUserStatsReceivedCallback.Unregister();
	OnUserStatsStoredCallback.Unregister();
	OnUserAchievementStoredCallback.Unregister();
	OnUserStatsUnloadedCallback.Unregister();
	OnUserAchievementIconFetchedCallback.Unregister();
#endif

	Super::Deinitialize();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		Steam API Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

void UUserStats::AttachLeaderboardUGC(const FOnAttachLeaderboardUGC& Callback, FSteamLeaderboard SteamLeaderboard, FSteamUGCHandle Handle)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsAttachLeaderboardUGC* Task = new FOnlineAsyncTaskSteamCoreUserStatsAttachLeaderboardUGC(this, Callback, SteamLeaderboard, Handle);
		QueueAsyncTask(Task);
	}
#endif
}

bool UUserStats::ClearAchievement(FString Name)
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->ClearAchievement(TCHAR_TO_UTF8(*Name));
	}
#endif

	return bResult;
}

void UUserStats::DownloadLeaderboardEntries(const FOnDownloadLeaderboardEntries& Callback, FSteamLeaderboard SteamLeaderboard, ESteamLeaderboardDataRequest DataRequest, int32 RangeStart, int32 RangeEnd)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsDownloadLeaderboardEntries* Task = new FOnlineAsyncTaskSteamCoreUserStatsDownloadLeaderboardEntries(this, Callback, SteamLeaderboard, DataRequest, RangeStart, RangeEnd);
		QueueAsyncTask(Task);
	}
#endif
}

void UUserStats::DownloadLeaderboardEntriesForUsers(const FOnDownloadLeaderboardEntriesForUsers& Callback, FSteamLeaderboard SteamLeaderboard, TArray<FSteamID> Users)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsDownloadLeaderboardEntriesForUsers* Task = new FOnlineAsyncTaskSteamCoreUserStatsDownloadLeaderboardEntriesForUsers(this, Callback, SteamLeaderboard, Users);
		QueueAsyncTask(Task);
	}
#endif
}

void UUserStats::FindLeaderboard(const FOnFindLeaderboard& Callback, FString LeaderboardName)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsFindLeaderboard* Task = new FOnlineAsyncTaskSteamCoreUserStatsFindLeaderboard(this, Callback, LeaderboardName);
		QueueAsyncTask(Task);
	}
#endif
}

void UUserStats::FindOrCreateLeaderboard(const FOnFindOrCreateLeaderboard& Callback, FString LeaderboardName, ESteamLeaderboardSortMethod SortMethod, ESteamLeaderboardDisplayType DisplayType)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsFindOrCreateLeaderboard* Task = new FOnlineAsyncTaskSteamCoreUserStatsFindOrCreateLeaderboard(this, Callback, LeaderboardName, SortMethod, DisplayType);
		QueueAsyncTask(Task);
	}
#endif
}

bool UUserStats::GetAchievement(FString Name, bool& bAchieved)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	bAchieved = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetAchievement(TCHAR_TO_UTF8(*Name), &bAchieved);
	}
#endif

	return bResult;
}

bool UUserStats::GetAchievementAchievedPercent(FString Name, float& OutPercent)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	OutPercent = 0.0f;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetAchievementAchievedPercent(TCHAR_TO_UTF8(*Name), &OutPercent);
	}
#endif

	return bResult;
}

bool UUserStats::GetAchievementAndUnlockTime(FString Name, bool& bAchieved, int32& OutUnlockTime)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	bAchieved = false;
	OutUnlockTime = 0;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		uint32 UnlockTime = 0;

		bResult = SteamUserStats()->GetAchievementAndUnlockTime(TCHAR_TO_UTF8(*Name), &bAchieved, &UnlockTime);

		OutUnlockTime = UnlockTime;
	}
#endif
	
	return bResult;
}

FString UUserStats::GetAchievementDisplayAttribute(FString Name, FString Key)
{
	LogSteamCoreVeryVerbose("Name (%s), Key (%s)", *Name, *Key);

	FString Result;

	if (Name.Len() == 0 || Key.Len() == 0)
	{
	
		return Result;
	}

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		const FTCHARToUTF8 ConvertedName(*Name);
		const FTCHARToUTF8 ConvertedKey(*Key);

		Result = UTF8_TO_TCHAR(SteamUserStats()->GetAchievementDisplayAttribute(ConvertedName.Get(), ConvertedKey.Get()));
	}
#endif

	return Result;
}

UTexture2D* UUserStats::GetAchievementIcon(FString Name)
{
	LogSteamCoreVeryVerbose("");

	UTexture2D* Texture = nullptr;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		const int ImageData = SteamUserStats()->GetAchievementIcon(TCHAR_TO_UTF8(*Name));
		Texture = GetSteamTexture(ImageData);
	}
#endif

	return Texture;
}

bool UUserStats::GetDownloadedLeaderboardEntry(FSteamLeaderboardEntries LeaderboardEntries, int32 Index, FSteamLeaderboardEntry& OutLeaderboardEntry, TArray<int32> Details, TArray<int32>& OutDetails)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	OutLeaderboardEntry = FSteamLeaderboardEntry();
	OutDetails.Empty();

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		OutDetails.SetNum(Details.Num());

		LeaderboardEntry_t LeaderboardEntry;

		bResult = SteamUserStats()->GetDownloadedLeaderboardEntry(LeaderboardEntries, Index, &LeaderboardEntry, OutDetails.GetData(), OutDetails.Num());

		if (bResult)
		{
			OutLeaderboardEntry = LeaderboardEntry;
		}
	}
#endif

	return bResult;
}

FString UUserStats::GetAchievementName(int32 Achievement)
{
	LogSteamCoreVeryVerbose("");

	FString Result;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		Result = UTF8_TO_TCHAR(SteamUserStats()->GetAchievementName(Achievement));
	}
#endif

	return Result;
}

bool UUserStats::GetGlobalStatInt(FString StatName, int32& OutData)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	OutData = 0;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		int64 pData;
		bResult = SteamUserStats()->GetGlobalStat(TCHAR_TO_UTF8(*StatName), &pData);
		OutData = pData;
	}
#endif

	return bResult;
}

bool UUserStats::GetGlobalStatFloat(FString StatName, float& OutData)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	OutData = 0.0f;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		double pData;
		bResult = SteamUserStats()->GetGlobalStat(TCHAR_TO_UTF8(*StatName), &pData);
		OutData = pData;
	}
#endif

	return bResult;
}

int32 UUserStats::GetGlobalStatHistoryInt(FString StatName, int32 HistoryDays, TArray<int32>& OutData)
{
	LogSteamCoreVeryVerbose("");

	int32 Result = 0;
	OutData.Empty();

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		TArray<int64> pData;
		pData.SetNum(HistoryDays);

		Result = SteamUserStats()->GetGlobalStatHistory(TCHAR_TO_UTF8(*StatName), pData.GetData(), HistoryDays);

		for (auto& Element : pData)
		{
			OutData.Add(Element);
		}
	}
#endif

	return Result;
}

int32 UUserStats::GetGlobalStatHistoryFloat(FString StatName, int32 HistoryDays, TArray<float>& OutData)
{
	LogSteamCoreVeryVerbose("");

	int32 Result = 0;
	OutData.Empty();

#if WITH_STEAMCORE
	if (SteamUserStats() && HistoryDays > 0)
	{
		TArray<double> DataArray;
		DataArray.SetNum(HistoryDays);

		Result = SteamUserStats()->GetGlobalStatHistory(TCHAR_TO_UTF8(*StatName), DataArray.GetData(), DataArray.Num());

		for (auto& Element : DataArray)
		{
			OutData.Add(Element);
		}
	}
#endif

	return Result;
}

bool UUserStats::GetAchievementProgressLimits(FString Name, int32& MinProgress, int32& MaxProgress)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	MinProgress = 0;
	MaxProgress = 0;

#if WITH_STEAMCORE
#if STEAM_VERSION >= 151
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetAchievementProgressLimits(TCHAR_TO_UTF8(*Name), &MinProgress, &MaxProgress);
	}
#endif
#endif

	return bResult;
}

bool UUserStats::GetAchievementProgressLimitsFloat(FString Name, float& MinProgress, float& MaxProgress)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	MinProgress = 0.0f;
	MaxProgress = 0.0f;

#if WITH_STEAMCORE
#if STEAM_VERSION >= 151
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetAchievementProgressLimits(TCHAR_TO_UTF8(*Name), &MinProgress, &MaxProgress);
	}
#endif
#endif

	return bResult;
}

ESteamLeaderboardDisplayType UUserStats::GetLeaderboardDisplayType(FSteamLeaderboard SteamLeaderboard)
{
	LogSteamCoreVeryVerbose("");

	ESteamLeaderboardDisplayType Result = ESteamLeaderboardDisplayType::None;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		Result = static_cast<ESteamLeaderboardDisplayType>(SteamUserStats()->GetLeaderboardDisplayType(SteamLeaderboard));
	}
#endif

	return Result;
}

int32 UUserStats::GetLeaderboardEntryCount(FSteamLeaderboard SteamLeaderboard)
{
	LogSteamCoreVeryVerbose("");

	int32 Result = 0;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		Result = SteamUserStats()->GetLeaderboardEntryCount(SteamLeaderboard);
	}
#endif

	return Result;
}

FString UUserStats::GetLeaderboardName(FSteamLeaderboard SteamLeaderboard)
{
	LogSteamCoreVeryVerbose("");

	FString Result;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		Result = UTF8_TO_TCHAR(SteamUserStats()->GetLeaderboardName(SteamLeaderboard));
	}
#endif

	return Result;
}

ESteamLeaderboardSortMethod UUserStats::GetLeaderboardSortMethod(FSteamLeaderboard SteamLeaderboard)
{
	LogSteamCoreVeryVerbose("");

	ESteamLeaderboardSortMethod Result = ESteamLeaderboardSortMethod::None;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		Result = static_cast<ESteamLeaderboardSortMethod>(SteamUserStats()->GetLeaderboardSortMethod(SteamLeaderboard));
	}
#endif

	return Result;
}

int32 UUserStats::GetMostAchievedAchievementInfo(FString& Name, float& OutPercent, bool& bAchieved)
{
	LogSteamCoreVeryVerbose("");

	int Result = 0;

	Name.Empty();
	OutPercent = 0.0f;
	bAchieved = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		TArray<char> DataArray;
		DataArray.SetNum(128);

		Result = SteamUserStats()->GetMostAchievedAchievementInfo(DataArray.GetData(), 128, &OutPercent, &bAchieved);

		Name = UTF8_TO_TCHAR(DataArray.GetData());
	}
#endif

	return Result;
}

int32 UUserStats::GetNextMostAchievedAchievementInfo(int32 IteratorPrevious, FString& Name, float& OutPercent, bool& bAchieved)
{
	LogSteamCoreVeryVerbose("");

	int Result = 0;

	Name.Empty();
	OutPercent = 0.0f;
	bAchieved = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		TArray<char> DataArray;
		DataArray.SetNum(128);

		Result = SteamUserStats()->GetNextMostAchievedAchievementInfo(IteratorPrevious, DataArray.GetData(), 128, &OutPercent, &bAchieved);

		Name = UTF8_TO_TCHAR(DataArray.GetData());
	}
#endif

	return Result;
}

int32 UUserStats::GetNumAchievements()
{
	LogSteamCoreVeryVerbose("");

	int32 Result = 0;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		Result = SteamUserStats()->GetNumAchievements();
	}
#endif

	return Result;
}

void UUserStats::GetNumberOfCurrentPlayers(const FOnGetNumberOfCurrentPlayers& Callback)
{
	LogSteamCoreVeryVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsGetNumberOfCurrentPlayers* Task = new FOnlineAsyncTaskSteamCoreUserStatsGetNumberOfCurrentPlayers(this, Callback);
		QueueAsyncTask(Task);
	}
#endif
}

bool UUserStats::GetUserStatInteger(FSteamID SteamIDUser, FString Name, int32& OutData)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;

	OutData = 0;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetUserStat(SteamIDUser, TCHAR_TO_UTF8(*Name), &OutData);
	}
#endif

	return bResult;
}

bool UUserStats::GetUserStatFloat(FSteamID SteamIDUser, FString Name, float& OutData)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	OutData = 0.0f;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetUserStat(SteamIDUser, TCHAR_TO_UTF8(*Name), &OutData);
	}
#endif

	return bResult;
}

bool UUserStats::GetUserAchievement(FSteamID SteamIDUser, FString Name, bool& bAchieved)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	bAchieved = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetUserAchievement(SteamIDUser, TCHAR_TO_UTF8(*Name), &bAchieved);
	}
#endif

	return bResult;
}

bool UUserStats::GetUserAchievementAndUnlockTime(FSteamID SteamIDUser, FString Name, bool& bAchieved, int32& OutUnlockTime)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	bAchieved = false;
	OutUnlockTime = 0;
	uint32 UnlockTime = 0;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		SteamUserStats()->GetUserAchievementAndUnlockTime(SteamIDUser, TCHAR_TO_UTF8(*Name), &bAchieved, &UnlockTime);
	}

	OutUnlockTime = UnlockTime;
#endif

	return bResult;
}

bool UUserStats::GetStatInt(FString Name, int32& OutData)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	OutData = 0;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetStat(TCHAR_TO_UTF8(*Name), &OutData);
	}
#endif

	return bResult;
}

bool UUserStats::GetStatFloat(FString Name, float& OutData)
{
	LogSteamCoreVeryVerbose("");

	bool bResult = false;
	OutData = 0.0f;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->GetStat(TCHAR_TO_UTF8(*Name), &OutData);
	}
#endif

	return bResult;
}

bool UUserStats::IndicateAchievementProgress(FString Name, int32 CurrentProgress, int32 MaxProgress)
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->IndicateAchievementProgress(TCHAR_TO_UTF8(*Name), CurrentProgress, MaxProgress);
	}
#endif

	return bResult;
}

bool UUserStats::RequestCurrentStats()
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->RequestCurrentStats();
	}
#endif

	return bResult;
}

void UUserStats::RequestGlobalAchievementPercentages(const FOnRequestGlobalAchievementPercentages& Callback)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsRequestGlobalAchievementPercentages* Task = new FOnlineAsyncTaskSteamCoreUserStatsRequestGlobalAchievementPercentages(this, Callback);
		QueueAsyncTask(Task);
	}
#endif
}

void UUserStats::RequestGlobalStats(const FOnRequestGlobalStats& Callback, int32 HistoryDays)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsRequestGlobalStats* Task = new FOnlineAsyncTaskSteamCoreUserStatsRequestGlobalStats(this, Callback, HistoryDays);
		QueueAsyncTask(Task);
	}
#endif
}

void UUserStats::RequestUserStats(const FOnRequestUserStats& Callback, FSteamID SteamID)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsRequestUserStats* Task = new FOnlineAsyncTaskSteamCoreUserStatsRequestUserStats(this, Callback, SteamID);
		QueueAsyncTask(Task);
	}
#endif
}

bool UUserStats::ResetAllStats(bool bAchievementsToo)
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->ResetAllStats(bAchievementsToo);
	}
#endif

	return bResult;
}

bool UUserStats::SetAchievement(FString Name)
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->SetAchievement(TCHAR_TO_UTF8(*Name));
	}
#endif

	return bResult;
}

bool UUserStats::SetStatInt(FString Name, int32 Data)
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->SetStat(TCHAR_TO_UTF8(*Name), Data);
	}
#endif

	return bResult;
}

bool UUserStats::SetStatFloat(FString Name, float Data)
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->SetStat(TCHAR_TO_UTF8(*Name), Data);
	}
#endif

	return bResult;
}

bool UUserStats::StoreStats()
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->StoreStats();
	}
#endif

	return bResult;
}

bool UUserStats::UpdateAvgRateStat(FString Name, float CountThisSession, float SessionLength)
{
	LogSteamCoreVerbose("");

	bool bResult = false;

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		bResult = SteamUserStats()->UpdateAvgRateStat(TCHAR_TO_UTF8(*Name), CountThisSession, SessionLength);
	}
#endif

	return bResult;
}

void UUserStats::UploadLeaderboardScore(const FOnUploadLeaderboardScore& Callback, FSteamLeaderboard SteamLeaderboard, ESteamLeaderboardUploadScoreMethod UploadScoreMethod, int32 Score, TArray<int32> ScoreDetails)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamUserStats())
	{
		FOnlineAsyncTaskSteamCoreUserStatsUploadLeaderboardScore* Task = new FOnlineAsyncTaskSteamCoreUserStatsUploadLeaderboardScore(this, Callback, SteamLeaderboard, UploadScoreMethod, Score, ScoreDetails);
		QueueAsyncTask(Task);
	}
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		Steam API Callbacks
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#if WITH_STEAMCORE
void UUserStats::OnUserStatsReceived(UserStatsReceived_t* pParam)
{
	LogSteamCoreVerbose("");

	auto Data = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	{
		UserStatsReceived.Broadcast(Data);
	});
}

void UUserStats::OnUserStatsStored(UserStatsStored_t* pParam)
{
	LogSteamCoreVerbose("");

	auto Data = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	{
		UserStatsStored.Broadcast(Data);
	});
}

void UUserStats::OnUserAchievementStored(UserAchievementStored_t* pParam)
{
	LogSteamCoreVerbose("");

	auto Data = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	{
		UserAchievementStored.Broadcast(Data);
	});
}

void UUserStats::OnUserStatsUnloaded(UserStatsUnloaded_t* pParam)
{
	LogSteamCoreVerbose("");

	auto Data = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	{
		UserStatsUnloaded.Broadcast(Data);
	});
}

void UUserStats::OnUserAchievementIconFetched(UserAchievementIconFetched_t* pParam)
{
	LogSteamCoreVerbose("");

	FUserAchievementIconFetched Data = *pParam;
	Data.Icon = GetSteamTexture(Data.m_nIconHandle);
	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	{
		UserAchievementIconFetched.Broadcast(Data);
	});
}
#endif