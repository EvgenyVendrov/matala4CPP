/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */

#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

int main()
{

	badkan::TestCase testcase;
	int grade = 0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0)
	{

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

		testcase.setname("Calculate bull and pgia")
			.CHECK_OUTPUT(calculateBullAndPgia("1234", "1234"), "4,0") // 4 bull, 0 pgia
			.CHECK_OUTPUT(calculateBullAndPgia("1234", "4321"), "0,4") // 0 bull, 4 pgia
			;

		// testcase.setname("Play with dummy choosers and guessers")
		// 	.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)	// guesser wins in one turn.
		// 	.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)  // guesser loses by running out of turns
		// 	.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101) // guesser loses technically by making an illegal guess (too long).
		// 	.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)   // chooser loses technically by choosing an illegal number (too long).
		// 	;

		// testcase.setname("Play with smart guesser");
		// RandomChooser randy;
		// SmartGuesser smarty;
		// for (uint i = 0; i < 100; ++i)
		// {
		// 	testcase.CHECK_EQUAL(play(randy, smarty, 4, 100) <= 100, true); // smarty should always win in at most 10 turns!
		// }

		////************************MY OWN TESTS************************////
		//bull&pgia method test:
		string chooser = "12345";
		testcase.setname("calculateBullAndPgia - sanity test")
			//first - checking the chooser string with diffrent permutations on its own digits
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "54231"), "0,5")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "15432"), "1,4")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "12534"), "2,3")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "12354"), "3,2")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, chooser), "5,0")
			//second - checking the chooser with a 'foreign' string
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "78999"), "0,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "18999"), "1,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "12999"), "2,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "12399"), "3,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "12349"), "4,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "71999"), "0,1")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "71299"), "0,2")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "71239"), "0,3")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "71234"), "0,4")
			//third - checking the chooser with permutations on a 'foreign' string
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "77771"), "0,1")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "77717"), "0,1")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "77177"), "0,1")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "71777"), "0,1")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "17777"), "1,0")
			//third - checking the chooser on some edge case's
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "11111"), "1,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "22222"), "1,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "33333"), "1,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "44444"), "1,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "55555"), "1,0");
		chooser = "1211";
		testcase.setname("calculateBullAndPgia - sanity test")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "1111"), "3,0")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "2112"), "1,2")
			.CHECK_OUTPUT(calculateBullAndPgia(chooser, "2221"), "2,0")
			//fourth - making sure there is an exception thrown checking two diffrent length strings
			.CHECK_THROWS(calculateBullAndPgia("123", "123456"));

		//*****************RandomGuesser methods test*****************

		// RandomGuesser randTestGuesser{};
		// calcFunOutput reply{5, 0};
		// //LEARN METHOD - **BEFORE** we created a new game - should throw:
		// testcase.setname("[RandomGuesser]learn - throws before starting new game test")
		// 	.CHECK_THROWS(randTestGuesser.learn(reply));
		// //now STARTING new game
		// testcase.setname("[RandomGuesser]startNewGame - throws on args which are <=0")
		// 	.CHECK_THROWS(randTestGuesser.startNewGame(0));
		// ///////////////////////////
		// testcase.setname("[RandomGuesser]startNewGame - throws on args which are <=0")
		// 	.CHECK_THROWS(randTestGuesser.startNewGame(-7));
		// //////////////////////////
		// testcase.setname("[RandomGuesser]startNewGame - sanity test")
		// 	.CHECK_OK(randTestGuesser.startNewGame(5));
		// //LEARN METHOD - sanity test:
		// //first - checking that the function works on logically correct numbers
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{4, 0};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{3, 0};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{2, 0};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{1, 0};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 0};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 1};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 2};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 3};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 4};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 5};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{1, 1};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{2, 2};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{2, 3};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ///////////////////////////////////////////
		// reply = calcFunOutput{3, 2};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ///////////////////////////////////////////
		// reply = calcFunOutput{4, 1};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// //////////////////////////////////////////
		// reply = calcFunOutput{1, 4};
		// testcase.setname("[RandomGuesser]learn - sanity test")
		// 	.CHECK_OK(randTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// //second - checking that the function throws on logically incorrect numbers
		// reply = calcFunOutput{6, 0};
		// testcase.setname("[RandomGuesser]learn - throwing exceptions test")
		// 	.CHECK_THROWS(randTestGuesser.learn(reply));
		// /////////////////////////////////////
		// reply = calcFunOutput{3, 3};
		// testcase.setname("[RandomGuesser]learn - throwing exceptions test")
		// 	.CHECK_THROWS(randTestGuesser.learn(reply));
		// ///////////////////////////////////
		// reply = calcFunOutput{70, 0};
		// testcase.setname("[RandomGuesser]learn - throwing exceptions test")
		// 	.CHECK_THROWS(randTestGuesser.learn(reply));
		// ///////////////////////////////////
		// //only validating that 'play' is working (not a smart guesser so shouldn't guess in any amount of guesses):
		// testcase.setname("[RandomGuesser]play- sanity test");
		// // .CHECK_OK(play(randy, randTestGuesser, 5, 10))
		// // .CHECK_THROWS(play(randy, randTestGuesser, 0, 10))
		// // .CHECK_THROWS(play(randy, randTestGuesser, -1, 10))
		// // .CHECK_THROWS(play(randy, randTestGuesser, 5, 0))
		// // .CHECK_THROWS(play(randy, randTestGuesser, 5, -1));

		// //*****************SmartGuesser methods test*****************

		// SmartGuesser smartTestGuesser{};
		// //LEARN METHOD - **BEFORE** we created a new game - should throw:
		// testcase.setname("[SmartGuesser]learn - throws before starting new game test")
		// 	.CHECK_THROWS(smartTestGuesser.learn(reply));
		// //now STARTING new game
		// testcase.setname("[SmartGuesser]startNewGame - throws on args which are <=0")
		// 	.CHECK_THROWS(smartTestGuesser.startNewGame(0));
		// ///////////////////////////
		// testcase.setname("[SmartGuesser]startNewGame - throws on args which are <=0")
		// 	.CHECK_THROWS(smartTestGuesser.startNewGame(-7));
		// //////////////////////////
		// testcase.setname("[SmartGuesser]startNewGame - sanity test")
		// 	.CHECK_OK(smartTestGuesser.startNewGame(5));
		// //LEARN METHOD - sanity test:
		// //first - checking that the function works on logically correct numbers
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{4, 0};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{3, 0};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{2, 0};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{1, 0};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 0};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 1};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 2};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 3};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 4};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{0, 5};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{1, 1};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{2, 2};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// reply = calcFunOutput{2, 3};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ///////////////////////////////////////////
		// reply = calcFunOutput{3, 2};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ///////////////////////////////////////////
		// reply = calcFunOutput{4, 1};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// //////////////////////////////////////////
		// reply = calcFunOutput{1, 4};
		// testcase.setname("[SmartGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// ////////////////////////////////////////////
		// //second - checking that the function throws on logically incorrect numbers
		// reply = calcFunOutput{6, 0};
		// testcase.setname("[SmartGuesser]learn - throwing exceptions test")
		// 	.CHECK_THROWS(smartTestGuesser.learn(reply));
		// /////////////////////////////////////
		// reply = calcFunOutput{3, 3};
		// testcase.setname("[SmartGuesser]learn - throwing exceptions test")
		// 	.CHECK_THROWS(smartTestGuesser.learn(reply));
		// ///////////////////////////////////
		// reply = calcFunOutput{70, 0};
		// testcase.setname("[SmartGuesser]learn - throwing exceptions test")
		// 	.CHECK_THROWS(smartTestGuesser.learn(reply));
		// ///////////////////////////////////
		// //validating that 'play' is working correctly :
		// testcase.setname("[SmartGuesser]play- sanity test")
		// 	.CHECK_OK(play(randy, randTestGuesser, 5, 10))
		// 	// .CHECK_THROWS(play(randy, randTestGuesser, 0, 10))
		// 	// .CHECK_THROWS(play(randy, randTestGuesser, -1, 10))
		// 	// .CHECK_THROWS(play(randy, randTestGuesser, 5, 0))
		// 	// .CHECK_THROWS(play(randy, randTestGuesser, 5, -1))
		// 	.CHECK_EQUAL(play(randy, smarty, 1, 100) <= 100, true)
		// 	.CHECK_EQUAL(play(randy, smarty, 2, 100) <= 100, true)
		// 	.CHECK_EQUAL(play(randy, smarty, 3, 100) <= 100, true)
		// 	.CHECK_EQUAL(play(randy, smarty, 4, 100) <= 100, true)
		// 	.CHECK_OK(play(randy, smarty, 5, 100))
		// 	.CHECK_OK(play(randy, smarty, 6, 100))
		// 	.CHECK_OK(play(randy, smarty, 7, 100))
		// 	.CHECK_OK(play(randy, smarty, 8, 100))
		// 	.CHECK_OK(play(randy, smarty, 9, 100))
		// 	.CHECK_OK(play(randy, smarty, 10, 100))
		// 	.CHECK_OK(play(randy, smarty, 70, 100));

		// //*****************ConstantGuesser methods test*****************
		// //this testcase will be 'smaller' because this class is the most basic
		// //LEARN METHOD - **BEFORE** we created a new game - should throw:
		// ConstantGuesser constantGuesserTest{"1234"};
		// testcase.setname("[ConstantGuesser]learn - throws before starting new game test")
		// 	.CHECK_THROWS(constantGuesserTest.learn(reply));
		// //now STARTING new game
		// testcase.setname("[ConstantGuesser]startNewGame - throws on args which are <=0")
		// 	.CHECK_THROWS(constantGuesserTest.startNewGame(0));
		// ///////////////////////////
		// testcase.setname("[ConstantGuesser]startNewGame - throws on args which are <=0")
		// 	.CHECK_THROWS(constantGuesserTest.startNewGame(-7));
		// //////////////////////////
		// testcase.setname("[ConstantGuesser]startNewGame - throws on args which are (!=) of the constant length")
		// 	.CHECK_THROWS(constantGuesserTest.startNewGame(8));
		// //////////////////////////
		// testcase.setname("[ConstantGuesser]startNewGame - sanity test")
		// 	.CHECK_OK(constantGuesserTest.startNewGame(4));
		// //LEARN METHOD - sanity test:
		// //first - checking that the function works on logically correct numbers
		// reply = calcFunOutput{0, 4};
		// testcase.setname("[ConstantGuesser]learn - sanity test")
		// 	.CHECK_OK(smartTestGuesser.learn(reply));
		// //////////////////////////

		// //*****************Chooser's methods test*****************
		// //another short test as the class not that complex
		// ConstantChooser c{"12345"};
		// testcase.setname("[ConstantChooser]choose - sanity test")
		// 	.CHECK_OK(c.choose(5));
		// testcase.setname("[ConstantChooser]choose - throw on diffrent length on choose")
		// 	.CHECK_THROWS(c.choose(7));
		// testcase.setname("[ConstantChooser]choose - throw on <=0 args")
		// 	.CHECK_THROWS(c.choose(0))
		// 	.CHECK_THROWS(c.choose(-4));
		// ///////////////////////
		grade = testcase.grade();
	}
	else
	{
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: " << grade << endl;
	return 0;
}
