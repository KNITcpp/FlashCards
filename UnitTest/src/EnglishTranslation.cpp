#include "DikiApi.h"
#include "gtest/gtest.h"
#include <string>


class DogTranslation: public testing::Test
{
protected:
	std::vector<TransWithExamp> validResult;
	DogTranslation();

};

DogTranslation::DogTranslation()
{
	validResult.resize(15);

	validResult[0]=
	{
		L"dog",
		L"pies",
		{
			{L"My dog has a very good sense of smell.", L"Mój pies ma bardzo dobry wêch."},
			{L"I walk my dog every day.", L"Codziennie wyprowadzam mojego psa."},
			{L"I have a dog.", L"Mam psa."},
			{L"This dog is big.", L"Ten pies jest du¿y."},
		}
	};

	validResult[1]=
	{
		L"dog",
		L"samiec (psa, lisa, wilka)",
		{
			{L"These dogs can be aggressive.", L"Te samce mog¹ byæ agresywne."},
			{L"Is it a dog or a bitch?", L"To samiec czy suczka?"},
		}
	};

	validResult[2]=
	{
		L"dog",
		L"³ajdak, szuja",
		{
			{L"He's a dog, you can't trust him.", L"To ³ajdak, nie mo¿esz mu ufaæ."},
			{L"He tried to lie to me, what a dog!", L"On próbowa³ mnie ok³amaæ, co za szuja!"},
		}
	};

	validResult[3]=
	{
		L"dog",
		L"lipa, szmelc, tandeta",
		{
			{L"This equipment is a dog!", L"Ten sprzêt to szmelc!"},
			{L"She sells dogs.", L"Ona sprzedaje tandetê."},
			{L"I won't give you even 10 dollars for this dog!", L"Nie dam ci nawet dziesiêciu dolarów za tê tandetê!"},
		}
	};

	validResult[4]=
	{
		L"dog",
		L"pokraka, maszkara (nieatrakcyjna kobieta)",
		{
			{L"Look at that woman. What a dog.", L"Popatrz na tamt¹ kobietê. Jaka pokraka."},
			{L"I love my sister, but I must admit that she's a dog.", L"Kocham moj¹ siostrê, ale muszê przyznaæ, ¿e jest maszkar¹."},
			{L"I married this dog because she's rich.", L"Poœlubi³em tê pokrakê, bo jest bogata."},
		}
	};

	validResult[5]=
	{
		L"dog",
		L"koleœ, ziomek",
		{
			{L"That's Peter, my best dog.", L"Poznaj Petera, mojego najlepszego ziomka."},
			{L"What's up, dog?", L"Co tam, ziomek?"},
		}
	};

	validResult[6]=
	{
		L"dog",
		L"pies na baby",
		{
			{L"Don't trust him, he's a real dog.", L"Nie ufaj mu, to prawdziwy pies na baby."},
			{L"Women should stay away from him, he's a dog.", L"Kobiety powinny trzymaæ siê od niego z daleka, to pies na baby."},
		}
	};

	validResult[7]=
	{
		L"dog",
		L"dwója, pa³a (ocena)",
		{
			{L"I got a dog from that test.", L"Dosta³em pa³ê z tego testu."},
			{L"I have to read this book or I'll get a dog.", L"Muszê przeczytaæ tê ksi¹¿kê, albo dostanê dwójê."},
		}
	};

	validResult[8]=
	{
		L"dog",
		L"iœæ blisko za kimœ, nie odstêpowaæ (jak pies)",
		{
			{L"You have to dog him, I want to know where he lives!", L"Musisz iœæ za nim blisko jak pies, chcê wiedzieæ, gdzie on mieszka!"},
			{L"This girl dogs me but I don't like her!", L"Ta dziewczyna chodzi blisko za mn¹ jak pies, ale ja jej nie lubiê!"},
		}
	};

	validResult[9]=
	{
		L"dog",
		L"gnêbiæ (gdy kogoœ gnêbi jakiœ problem lub pech), uprzykrzaæ",
		{
			{L"Don't let it dog you, I'll help you find a job.", L"Nie pozwól, ¿eby ciê to gnêbi³o, pomogê ci znaleŸæ pracê."},
			{L"This problem has been dogging me for a year now.", L"Ten problem gnêbi mnie ju¿ od roku."},
		}
	};

	validResult[10]=
	{
		L"dog",
		L"uprawiaæ seks na pieska",
		{
			{L"I dogged Jane yesterday!", L"Wczoraj uprawia³em z Jane seks na pieska!"},
			{L"Jane doesn't like to dog.", L"Jane nie lubi uprawiaæ seksu na pieska."},
		}
	};

	validResult[11]=
	{
		L"dog",
		L"nawaliæ, spieprzyæ, schrzaniæ",
		{
			{L"Do not dog this, I won't give you another chance.", L"Nie spieprz tego, nie dam ci kolejnej szansy."},
			{L"If you dog again, I'll have to break up with you.", L"Jeœli znowu nawalisz, bêdê musia³ z tob¹ zerwaæ."},
		}
	};

	validResult[12]=
	{
		L"dog",
		L"do³owaæ, zamartwiaæ",
		{
			{L"You can't dog your mother, don't tell her about the accident.", L"Nie mo¿esz do³owaæ swojej matki, nie mów jej o wypadku."},
			{L"I don't want to dog you, but I think we have a serious problem with our son.", L"Nie chcê ciê zamartwiaæ, ale myœlê, ¿e mamy powa¿ny problem z naszym synem."},
		}
	};

	validResult[13]=
	{
		L"dog",
		L"œledziæ, tropiæ",
		{

		}
	};

	validResult[14]=
	{
		L"dog it",
		L"olewaæ, nie dawaæ z siebie wszystkiego",
		{
			{L"He was accused of dogging it by his boss.", L"On zosta³ oskar¿ony o nie dawanie z siebie wszystkiego przez swojego szefa."},
		}
	};
}


TEST_F(DogTranslation, getTranslation)
{
	DikiApi api;
	const std::wstring TO_TRANSLATE=L"dog";
	std::vector<TransWithExamp> translation=api.getTranslation(TO_TRANSLATE);

	ASSERT_EQ(translation.size(), validResult.size());

	for(int i=0; i<validResult.size(); ++i)
	{
		EXPECT_EQ(translation[i].translation, validResult[i].translation) << i;
		EXPECT_EQ(translation[i].word, validResult[i].word) << i;
		ASSERT_EQ(translation[i].example.size(), validResult[i].example.size()) << i;
		
		for(int k=0; k<validResult[i].example.size(); ++k)
		{
			std::string index="i=";
			index += i + "k=" + k;

			EXPECT_EQ(validResult[i].example[k].sentence, translation[i].example[k].sentence) << index;
			EXPECT_EQ(validResult[i].example[k].sentenceTranslation, translation[i].example[k].sentenceTranslation) <<index;
		}
	}
}





class KeepTranslation: public testing::Test
{
	protected:
	std::vector<TransWithExamp> validResult;
	KeepTranslation();
};


KeepTranslation::KeepTranslation()
{
	validResult.resize(22);

	validResult[0]=
	{
		L"keep",
		L"trzymaæ, zatrzymywaæ, zachowywaæ (mieæ coœ na sta³e lub przez jakiœ czas)",
		{
			{L"May I keep it?", L"Czy mogê to zatrzymaæ?"},
			{L"You can keep the book. I have another copy.", L"Mo¿esz zachowaæ tê ksi¹¿kê. Mam jeszcze jedn¹ kopiê."},
		}
	};

	validResult[1]=
	{
		L"keep",
		L"powstrzymywaæ, kazaæ, trzymaæ, musieæ (zmusiæ kogoœ do zrobienia czegoœ, co powstrzyma go przed zrobieniem czegoœ innego)",
		{
			{L"Sorry to keep you waiting.", L"Przepraszam, ¿e musia³eœ czekaæ."},
			{L"Don't let her keep you from your responsibilities.", L"Nie pozwól jej powstrzymywaæ ciê od wykonywania swoich obowi¹zków."},
		}
	};

	validResult[2]=
	{
		L"keep",
		L"zatrzymywaæ (sprawiaæ, ¿e ktoœ przybêdzie póŸniej, ni¿ planowa³)",
		{
			{L"I won't keep you any longer, but I hope you learned something.", L"Nie bêdê ciê d³u¿ej zatrzymywaæ, ale mam nadziejê, ¿e czegoœ siê nauczy³eœ."},
		}
	};

	validResult[3]=
	{
		L"keep",
		L"prowadziæ (np. pamiêtnik, zapiski, rejestr)",
		{
			{L"I kept a diary throughout my teenage years.", L"Prowadzi³am pamiêtnik jak by³am nastolatk¹."},
		}
	};

	validResult[4]=
	{
		L"keep",
		L"zachowywaæ œwie¿oœæ, pozostawaæ œwie¿ym (o jedzeniu lub piciu)",
		{
			{L"Bread keeps well for a few days in a wooden box.", L"Chleb zachowuje œwie¿oœæ przez kilka dni w drewnianym pude³ku."},
		}
	};

	validResult[5]=
	{
		L"keep",
		L"utrzymywaæ (kogoœ jak¹œ sum¹ pieniêdzy, np. rodzinê)",
		{
			{L"You won't be able to keep a family on just one salary.", L"Nie bêdziesz w stanie utrzymaæ rodziny z tylko jednej wyp³aty."},
		}
	};

	validResult[6]=
	{
		L"keep",
		L"hodowaæ, trzymaæ (zwierzêta)",
		{
			{L"My grandma keeps cows and pigs.", L"Moja babcia hoduje krowy i œwinie."},
		}
	};

	validResult[7]=
	{
		L"keep",
		L"zachowywaæ, zostawaæ, pozostawaæ (w jakimœ stanie), utrzymywaæ (np. porz¹dek gdzieœ)",
		{
			{L"She always keeps her room clean.", L"Ona zawsze utrzymuje swój pokój w czystoœci."},
			{L"Keep calm.", L"Zachowaj spokój."},
			{L"He couldn't keep his balance.", L"Nie móg³ utrzymaæ równowagi."},
		}
	};

	validResult[8]=
	{
		L"keep",
		L"robiæ ci¹gle (kontynuowaæ lub powtarzaæ robienie czegoœ)",
		{
			{L"She keeps going on about her issues.", L"Ona ci¹gle nawija o swoich problemach."},
		}
	};

	validResult[9]=
	{
		L"keep",
		L"przechowywaæ, trzymaæ (np. na póŸniej)",
		{
			{L"Could you keep my jewellery for a few days?", L"Czy móg³byœ przechowaæ moj¹ bi¿uteriê przez kilka dni?"},
		}
	};

	validResult[10]=
	{
		L"keep",
		L"dotrzymywaæ (np. s³owa, obietnicy, zobowi¹zania)",
		{
			{L"Don't worry, I won't tell anybody. I always keep my word.", L"Nie martw siê, nikomu nie powiem. Ja zawsze dotrzymujê s³owa."},
			{LR"("Will you keep your promise?" "Yes, of course.")", LR"("Czy dotrzymasz swojej obietnicy?" "Oczywiœcie, ¿e tak.")"},
		}
	};

	validResult[11]=
	{
		L"keep",
		L"przestrzegaæ (praw, zasad lub tradycji)",
		{
			{L"Not keeping the rules may turn out deadly.", L"Nie przestrzeganie zasad mo¿e okazaæ siê œmiertelne."},
			{L"She never keeps rules, so nobody wants to play with her.", L"Ona nigdy nie przestrzega zasad, wiêc nikt nie chce z ni¹ graæ."},
		}
	};

	validResult[12]=
	{
		L"keep",
		L"przestrzegaæ (zasad religijnych), obchodziæ (tradycje religijne, np. post)",
		{
			{L"Some of my family don't keep Sabbath.", L"Niektórzy z mojej rodziny nie przestrzegaj¹ zasad szabatu."},
		}
	};

	validResult[13]=
	{
		L"keep",
		L"trzymaæ, zajmowaæ (np. miejsce dla kogoœ)",
		{
			{L"Could you keep a seat for me?", L"Czy móg³byœ zaj¹æ mi miejsce?"},
		}
	};

	validResult[14]=
	{
		L"keep",
		L"mieæ, prowadziæ (ma³y biznes lub interes)",
		{
			{L"My grandparents used to keep a small animal shop.", L"Moi dziadkowie prowadzili ma³y sklep zoologiczny."},
		}
	};

	validResult[15]=
	{
		L"keep",
		L"ochraniaæ, pilnowaæ, strzec",
		{
			{L"Your data is well kept.", L"Twoje dane s¹ dok³adnie chronione."},
			{L"The celebrity claims she keeps her privacy, but she stars in a reality show.", L"Celebrytka twierdzi, ¿e chroni swoj¹ prywatnoœæ, ale wystêpuje w reality show."},
		}
	};

	validResult[16]=
	{
		L"keep",
		L"utrzymanie, wikt",
		{
			{L"While she's in college, she's on my keep.", L"Podczas kiedy ona jest na studiach, ona jest na moim utrzymaniu."},
			{L"I've been on my aunt's keep for years.", L"By³em na utrzymaniu mojej ciotki latami."},
		}
	};

	validResult[17]=
	{
		L"keep",
		L"don¿on (typ wie¿y zamkowej)",
		{
			{L"The keep was destroyed during the war.", L"Don¿on zosta³ zniszczony podczas wojny."},
		}
	};

	validResult[18]=
	{
		L"keep to something",
		L"trzymaæ siê czegoœ (np. drogi, umowy, obietnicy, postanowienia)",
		{
		}
	};

	validResult[19]=
	{
		L"keep something to something",
		L"utrzymywaæ coœ na jakimœ poziomie (np. ceny na niskim poziomie)",
		{
		}
	};

	validResult[20]=
	{
		L"keep oneself to oneself",
		L"trzymaæ siê na uboczu, trzymaæ siê z dala od innych, byæ zamkniêtym w sobie",
		{
		}
	};

		validResult[21]=
	{
		L"keep something to oneself",
		L"zachowaæ coœ dla siebie",
		{
		}
	};
}


TEST_F(KeepTranslation, getTranslation) //TODO: refactor, because it repeats code of dog translation test
{
	DikiApi api;
	const std::wstring TO_TRANSLATE=L"keep";
	std::vector<TransWithExamp> translation=api.getTranslation(TO_TRANSLATE);

	ASSERT_EQ(translation.size(), validResult.size());

	for(int i=0; i<validResult.size(); ++i)
	{
		EXPECT_EQ(translation[i].translation, validResult[i].translation) << i;
		EXPECT_EQ(translation[i].word, validResult[i].word) << i;
		ASSERT_EQ(translation[i].example.size(), validResult[i].example.size()) << i;
		
		for(int k=0; k<validResult[i].example.size(); ++k)
		{
			std::string index="i=";
			index += i + "k=" + k;

			EXPECT_EQ(validResult[i].example[k].sentence, translation[i].example[k].sentence) << index;
			EXPECT_EQ(validResult[i].example[k].sentenceTranslation, translation[i].example[k].sentenceTranslation) <<index;
		}
	}
}


TEST(TranslatingNotExistingWord, alwaysReturnNothing)
{
	const std::wstring NOT_EXISTING_WORD=L"asdasdasdasdasdasdasd";
	DikiApi api;
	std::vector<TransWithExamp> translation=api.getTranslation(NOT_EXISTING_WORD);

	EXPECT_EQ(translation.size(), 0);
}







//TODO: test translations in a row
//TODO: change file name to DikiApiTest
//TODO: mock websiteFetcher
//TODO: split unit tests and integration tests into separate projects
//TODO: split class DikiApi and WebsiteFetcher into 3 separate classess: one that fetches website code, second that interprets this code and gets translations from it, third that combines the first two and makes api for Diki. First two classes should be tested by unit tests and third by integration test
//TODO: delete loops from tests
//TODO: apply KISS rule, 
//TODO: move data from fixture's constructors to tests' body
