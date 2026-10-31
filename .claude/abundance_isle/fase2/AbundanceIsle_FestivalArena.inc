AbundanceIsle_FestivalArena_EventScript_Receptionist::
	lock
	faceplayer
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 14, AbundanceIsle_FestivalArena_EventScript_Receptionist_Normal
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, AbundanceIsle_FestivalArena_EventScript_Receptionist_Saturday
AbundanceIsle_FestivalArena_EventScript_Receptionist_Normal::
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, AbundanceIsle_FestivalArena_EventScript_Receptionist_Done
	random 4
	copyvar VAR_ABUNDANCE_ARENA_PICK, VAR_RESULT
	msgbox AbundanceIsle_FestivalArena_EventScript_Receptionist_TextToday, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_Receptionist_Done::
	msgbox AbundanceIsle_FestivalArena_EventScript_Receptionist_TextDone, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_Receptionist_TextToday:
	.string "Welcome to the Festival Arena!\n"
	.string "Today's challenger is waiting\n"
	.string "on the benches. Go talk to them!$"
AbundanceIsle_FestivalArena_EventScript_Receptionist_TextDone:
	.string "That's today's match! Come back\n"
	.string "tomorrow for a new challenger.$"

AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_Rest
	goto_if_ne VAR_ABUNDANCE_ARENA_PICK, 0, AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_Rest
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_TextChallenge, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_ARENA_LEON
	trainerbattle_no_intro TRAINER_ABUNDANCE_ARENA_LEON, AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_ARENA
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_Rest::
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_TextRest, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_TextChallenge:
	.string "{SPEAKER NAME_LEON}So I'm today's challenger.\n"
	.string "Let's give the crowd a show!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_TextBeaten:
	.string "Leon: What a match!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerLeft1_TextRest:
	.string "{SPEAKER NAME_LEON}I'm just watching today.$"

AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_Rest
	goto_if_ne VAR_ABUNDANCE_ARENA_PICK, 1, AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_Rest
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_TextChallenge, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_ARENA_CYNTHIA
	trainerbattle_no_intro TRAINER_ABUNDANCE_ARENA_CYNTHIA, AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_ARENA
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_Rest::
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_TextRest, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_TextChallenge:
	.string "{SPEAKER NAME_CYNTHIA}So I'm today's challenger.\n"
	.string "Let's give the crowd a show!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_TextBeaten:
	.string "Cynthia: What a match!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerLeft2_TextRest:
	.string "{SPEAKER NAME_CYNTHIA}I'm just watching today.$"

AbundanceIsle_FestivalArena_EventScript_ChallengerRight1::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_Rest
	goto_if_ne VAR_ABUNDANCE_ARENA_PICK, 2, AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_Rest
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_TextChallenge, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_ARENA_DIANTHA
	trainerbattle_no_intro TRAINER_ABUNDANCE_ARENA_DIANTHA, AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_ARENA
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_Rest::
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_TextRest, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_TextChallenge:
	.string "{SPEAKER NAME_DIANTHA}So I'm today's challenger.\n"
	.string "Let's give the crowd a show!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_TextBeaten:
	.string "Diantha: What a match!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerRight1_TextRest:
	.string "{SPEAKER NAME_DIANTHA}I'm just watching today.$"

AbundanceIsle_FestivalArena_EventScript_ChallengerRight2::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_Rest
	goto_if_ne VAR_ABUNDANCE_ARENA_PICK, 3, AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_Rest
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_TextChallenge, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_ARENA_VOLKNER
	trainerbattle_no_intro TRAINER_ABUNDANCE_ARENA_VOLKNER, AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_ARENA
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_Rest::
	msgbox AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_TextRest, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_TextChallenge:
	.string "{SPEAKER NAME_VOLKNER}So I'm today's challenger.\n"
	.string "Let's give the crowd a show!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_TextBeaten:
	.string "Volkner: What a match!$"
AbundanceIsle_FestivalArena_EventScript_ChallengerRight2_TextRest:
	.string "{SPEAKER NAME_VOLKNER}I'm just watching today.$"

AbundanceIsle_FestivalArena_EventScript_Receptionist_Saturday::
	msgbox AbundanceIsle_FestivalArena_EventScript_Receptionist_TextSaturday, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_Receptionist_TextSaturday:
	.string "Saturdays are special! The benches\n"
	.string "are empty...\p"
	.string "...because two very special guests\n"
	.string "are waiting by the field. Go on!$"

AbundanceIsle_FestivalArena_EventScript_SaturdayN::
	goto AbundanceIsle_FestivalArena_EventScript_SaturdayDuo

AbundanceIsle_FestivalArena_EventScript_SaturdayHilda::
	goto AbundanceIsle_FestivalArena_EventScript_SaturdayDuo

AbundanceIsle_FestivalArena_EventScript_SaturdayDuo::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_Done
	msgbox AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_TextChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_No
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_N_AND_HILDA
	trainerbattle_no_intro TRAINER_ABUNDANCE_N_AND_HILDA, AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_ARENA
	msgbox AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_No::
	release
	end

AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_Done::
	msgbox AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_TextChallenge:
	.string "{SPEAKER NAME_N}{PLAYER}! The crowd wants a double\n"
	.string "battle. Will you give them one?\p"
	.string "{SPEAKER NAME_HILDA}Don't hold back. We won't!$"
AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_TextBeaten:
	.string "N: The crowd sounds... happy.$"
AbundanceIsle_FestivalArena_EventScript_SaturdayDuo_TextAfter:
	.string "{SPEAKER NAME_HILDA}Every Saturday we come here. It's\n"
	.string "the only crowd N doesn't mind.$"

AbundanceIsle_FestivalArena_EventScript_Fan1::
	msgbox AbundanceIsle_FestivalArena_EventScript_Fan1_Text, MSGBOX_NPC
	end

AbundanceIsle_FestivalArena_EventScript_Fan1_Text:
	.string "Every day there's a new\n"
	.string "challenger. I never miss one!$"

AbundanceIsle_FestivalArena_EventScript_Fan2::
	msgbox AbundanceIsle_FestivalArena_EventScript_Fan2_Text, MSGBOX_NPC
	end

AbundanceIsle_FestivalArena_EventScript_Fan2_Text:
	.string "I saw a Champion here yesterday!\n"
	.string "Or was it a Gym Leader?$"

AbundanceIsle_FestivalArena_EventScript_Fan3::
	msgbox AbundanceIsle_FestivalArena_EventScript_Fan3_Text, MSGBOX_NPC
	end

AbundanceIsle_FestivalArena_EventScript_Fan3_Text:
	.string "The festival only came back once\n"
	.string "spring did. Thank you, kid!$"

AbundanceIsle_FestivalArena_EventScript_TodaysBoard::
	msgbox AbundanceIsle_FestivalArena_EventScript_TodaysBoard_Text, MSGBOX_SIGN
	end

AbundanceIsle_FestivalArena_EventScript_TodaysBoard_Text:
	.string "FESTIVAL ARENA\n"
	.string "One challenger a day!\p"
	.string "Ask at the counter to see who\n"
	.string "is waiting on the benches.$"

