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
			{L"My dog has a very good sense of smell.", L"M�j pies ma bardzo dobry w�ch."},
			{L"I walk my dog every day.", L"Codziennie wyprowadzam mojego psa."},
			{L"I have a dog.", L"Mam psa."},
			{L"This dog is big.", L"Ten pies jest du�y."},
		}
	};

	validResult[1]=
	{
		L"dog",
		L"samiec (psa, lisa, wilka)",
		{
			{L"These dogs can be aggressive.", L"Te samce mog� by� agresywne."},
			{L"Is it a dog or a bitch?", L"To samiec czy suczka?"},
		}
	};

	validResult[2]=
	{
		L"dog",
		L"�ajdak, szuja",
		{
			{L"He's a dog, you can't trust him.", L"To �ajdak, nie mo�esz mu ufa�."},
			{L"He tried to lie to me, what a dog!", L"On pr�bowa� mnie ok�ama�, co za szuja!"},
		}
	};

	validResult[3]=
	{
		L"dog",
		L"lipa, szmelc, tandeta",
		{
			{L"This equipment is a dog!", L"Ten sprz�t to szmelc!"},
			{L"She sells dogs.", L"Ona sprzedaje tandet�."},
			{L"I won't give you even 10 dollars for this dog!", L"Nie dam ci nawet dziesi�ciu dolar�w za t� tandet�!"},
		}
	};

	validResult[4]=
	{
		L"dog",
		L"pokraka, maszkara (nieatrakcyjna kobieta)",
		{
			{L"Look at that woman. What a dog.", L"Popatrz na tamt� kobiet�. Jaka pokraka."},
			{L"I love my sister, but I must admit that she's a dog.", L"Kocham moj� siostr�, ale musz� przyzna�, �e jest maszkar�."},
			{L"I married this dog because she's rich.", L"Po�lubi�em t� pokrak�, bo jest bogata."},
		}
	};

	validResult[5]=
	{
		L"dog",
		L"kole�, ziomek",
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
			{L"Women should stay away from him, he's a dog.", L"Kobiety powinny trzyma� si� od niego z daleka, to pies na baby."},
		}
	};

	validResult[7]=
	{
		L"dog",
		L"dw�ja, pa�a (ocena)",
		{
			{L"I got a dog from that test.", L"Dosta�em pa�� z tego testu."},
			{L"I have to read this book or I'll get a dog.", L"Musz� przeczyta� t� ksi��k�, albo dostan� dw�j�."},
		}
	};

	validResult[8]=
	{
		L"dog",
		L"i�� blisko za kim�, nie odst�powa� (jak pies)",
		{
			{L"You have to dog him, I want to know where he lives!", L"Musisz i�� za nim blisko jak pies, chc� wiedzie�, gdzie on mieszka!"},
			{L"This girl dogs me but I don't like her!", L"Ta dziewczyna chodzi blisko za mn� jak pies, ale ja jej nie lubi�!"},
		}
	};

	validResult[9]=
	{
		L"dog",
		L"gn�bi� (gdy kogo� gn�bi jaki� problem lub pech), uprzykrza�",
		{
			{L"Don't let it dog you, I'll help you find a job.", L"Nie pozw�l, �eby ci� to gn�bi�o, pomog� ci znale�� prac�."},
			{L"This problem has been dogging me for a year now.", L"Ten problem gn�bi mnie ju� od roku."},
		}
	};

	validResult[10]=
	{
		L"dog",
		L"uprawia� seks na pieska",
		{
			{L"I dogged Jane yesterday!", L"Wczoraj uprawia�em z Jane seks na pieska!"},
			{L"Jane doesn't like to dog.", L"Jane nie lubi uprawia� seksu na pieska."},
		}
	};

	validResult[11]=
	{
		L"dog",
		L"nawali�, spieprzy�, schrzani�",
		{
			{L"Do not dog this, I won't give you another chance.", L"Nie spieprz tego, nie dam ci kolejnej szansy."},
			{L"If you dog again, I'll have to break up with you.", L"Je�li znowu nawalisz, b�d� musia� z tob� zerwa�."},
		}
	};

	validResult[12]=
	{
		L"dog",
		L"do�owa�, zamartwia�",
		{
			{L"You can't dog your mother, don't tell her about the accident.", L"Nie mo�esz do�owa� swojej matki, nie m�w jej o wypadku."},
			{L"I don't want to dog you, but I think we have a serious problem with our son.", L"Nie chc� ci� zamartwia�, ale my�l�, �e mamy powa�ny problem z naszym synem."},
		}
	};

	validResult[13]=
	{
		L"dog",
		L"�ledzi�, tropi�",
		{

		}
	};

	validResult[14]=
	{
		L"dog it",
		L"olewa�, nie dawa� z siebie wszystkiego",
		{
			{L"He was accused of dogging it by his boss.", L"On zosta� oskar�ony o nie dawanie z siebie wszystkiego przez swojego szefa."},
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
		L"trzyma�, zatrzymywa�, zachowywa� (mie� co� na sta�e lub przez jaki� czas)",
		{
			{L"May I keep it?", L"Czy mog� to zatrzyma�?"},
			{L"You can keep the book. I have another copy.", L"Mo�esz zachowa� t� ksi��k�. Mam jeszcze jedn� kopi�."},
		}
	};

	validResult[1]=
	{
		L"keep",
		L"powstrzymywa�, kaza�, trzyma�, musie� (zmusi� kogo� do zrobienia czego�, co powstrzyma go przed zrobieniem czego� innego)",
		{
			{L"Sorry to keep you waiting.", L"Przepraszam, �e musia�e� czeka�."},
			{L"Don't let her keep you from your responsibilities.", L"Nie pozw�l jej powstrzymywa� ci� od wykonywania swoich obowi�zk�w."},
		}
	};

	validResult[2]=
	{
		L"keep",
		L"zatrzymywa� (sprawia�, �e kto� przyb�dzie p�niej, ni� planowa�)",
		{
			{L"I won't keep you any longer, but I hope you learned something.", L"Nie b�d� ci� d�u�ej zatrzymywa�, ale mam nadziej�, �e czego� si� nauczy�e�."},
		}
	};

	validResult[3]=
	{
		L"keep",
		L"prowadzi� (np. pami�tnik, zapiski, rejestr)",
		{
			{L"I kept a diary throughout my teenage years.", L"Prowadzi�am pami�tnik jak by�am nastolatk�."},
		}
	};

	validResult[4]=
	{
		L"keep",
		L"zachowywa� �wie�o��, pozostawa� �wie�ym (o jedzeniu lub piciu)",
		{
			{L"Bread keeps well for a few days in a wooden box.", L"Chleb zachowuje �wie�o�� przez kilka dni w drewnianym pude�ku."},
		}
	};

	validResult[5]=
	{
		L"keep",
		L"utrzymywa� (kogo� jak�� sum� pieni�dzy, np. rodzin�)",
		{
			{L"You won't be able to keep a family on just one salary.", L"Nie b�dziesz w stanie utrzyma� rodziny z tylko jednej wyp�aty."},
		}
	};

	validResult[6]=
	{
		L"keep",
		L"hodowa�, trzyma� (zwierz�ta)",
		{
			{L"My grandma keeps cows and pigs.", L"Moja babcia hoduje krowy i �winie."},
		}
	};

	validResult[7]=
	{
		L"keep",
		L"zachowywa�, zostawa�, pozostawa� (w jakim� stanie), utrzymywa� (np. porz�dek gdzie�)",
		{
			{L"She always keeps her room clean.", L"Ona zawsze utrzymuje sw�j pok�j w czysto�ci."},
			{L"Keep calm.", L"Zachowaj spok�j."},
			{L"He couldn't keep his balance.", L"Nie m�g� utrzyma� r�wnowagi."},
		}
	};

	validResult[8]=
	{
		L"keep",
		L"robi� ci�gle (kontynuowa� lub powtarza� robienie czego�)",
		{
			{L"She keeps going on about her issues.", L"Ona ci�gle nawija o swoich problemach."},
		}
	};

	validResult[9]=
	{
		L"keep",
		L"przechowywa�, trzyma� (np. na p�niej)",
		{
			{L"Could you keep my jewellery for a few days?", L"Czy m�g�by� przechowa� moj� bi�uteri� przez kilka dni?"},
		}
	};

	validResult[10]=
	{
		L"keep",
		L"dotrzymywa� (np. s�owa, obietnicy, zobowi�zania)",
		{
			{L"Don't worry, I won't tell anybody. I always keep my word.", L"Nie martw si�, nikomu nie powiem. Ja zawsze dotrzymuj� s�owa."},
			{LR"("Will you keep your promise?" "Yes, of course.")", LR"("Czy dotrzymasz swojej obietnicy?" "Oczywi�cie, �e tak.")"},
		}
	};

	validResult[11]=
	{
		L"keep",
		L"przestrzega� (praw, zasad lub tradycji)",
		{
			{L"Not keeping the rules may turn out deadly.", L"Nie przestrzeganie zasad mo�e okaza� si� �miertelne."},
			{L"She never keeps rules, so nobody wants to play with her.", L"Ona nigdy nie przestrzega zasad, wi�c nikt nie chce z ni� gra�."},
		}
	};

	validResult[12]=
	{
		L"keep",
		L"przestrzega� (zasad religijnych), obchodzi� (tradycje religijne, np. post)",
		{
			{L"Some of my family don't keep Sabbath.", L"Niekt�rzy z mojej rodziny nie przestrzegaj� zasad szabatu."},
		}
	};

	validResult[13]=
	{
		L"keep",
		L"trzyma�, zajmowa� (np. miejsce dla kogo�)",
		{
			{L"Could you keep a seat for me?", L"Czy m�g�by� zaj�� mi miejsce?"},
		}
	};

	validResult[14]=
	{
		L"keep",
		L"mie�, prowadzi� (ma�y biznes lub interes)",
		{
			{L"My grandparents used to keep a small animal shop.", L"Moi dziadkowie prowadzili ma�y sklep zoologiczny."},
		}
	};

	validResult[15]=
	{
		L"keep",
		L"ochrania�, pilnowa�, strzec",
		{
			{L"Your data is well kept.", L"Twoje dane s� dok�adnie chronione."},
			{L"The celebrity claims she keeps her privacy, but she stars in a reality show.", L"Celebrytka twierdzi, �e chroni swoj� prywatno��, ale wyst�puje w reality show."},
		}
	};

	validResult[16]=
	{
		L"keep",
		L"utrzymanie, wikt",
		{
			{L"While she's in college, she's on my keep.", L"Podczas kiedy ona jest na studiach, ona jest na moim utrzymaniu."},
			{L"I've been on my aunt's keep for years.", L"By�em na utrzymaniu mojej ciotki latami."},
		}
	};

	validResult[17]=
	{
		L"keep",
		L"don�on (typ wie�y zamkowej)",
		{
			{L"The keep was destroyed during the war.", L"Don�on zosta� zniszczony podczas wojny."},
		}
	};

	validResult[18]=
	{
		L"keep to something",
		L"trzyma� si� czego� (np. drogi, umowy, obietnicy, postanowienia)",
		{
		}
	};

	validResult[19]=
	{
		L"keep something to something",
		L"utrzymywa� co� na jakim� poziomie (np. ceny na niskim poziomie)",
		{
		}
	};

	validResult[20]=
	{
		L"keep oneself to oneself",
		L"trzyma� si� na uboczu, trzyma� si� z dala od innych, by� zamkni�tym w sobie",
		{
		}
	};

		validResult[21]=
	{
		L"keep something to oneself",
		L"zachowa� co� dla siebie",
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
