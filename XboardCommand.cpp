#include "XboardCommand.h"

namespace chess {
	XboardCommand::XboardCommand(Engine& e) : engine(e) {
		mapSize = sizeof(m) / sizeof(m[0]);
	}

	bool XboardCommand::hXboard(const std::string& input, std::string& output) {
		//This command will be sent once immediately after your engine process is started.You can use it to put your engine into "xboard mode" if that is needed.If your engine prints a prompt to ask for user input, you must turn off the promptand output a newline when the "xboard" command comes in.
		output = "";
		return true;
	}

	bool XboardCommand::hProtover(const std::string& input, std::string& output)
	{
		//protover N
		//Beginning in protocol version 2 (in which N = 2), this command will be sent immediately after the "xboard" command.If you receive some other command immediately after "xboard" (such as "new"), you can assume that protocol version 1 is in use.The "protover" command is the only new command that xboard always sends in version 2. All other new commands to the engine are sent only if the engine first enables them with the "feature" command.Protocol versions will always be simple integers so that they can easily be compared.
		//Your engine should reply to the protover command by sending the "feature" command(see below) with the list of non - default feature settings that you require, if any.
		//Your engine should never refuse to run due to receiving a higher protocol version number than it is expecting!New protocol versions will always be compatible with older ones by default; the larger version number is simply a hint that additional "feature" command options added in later protocol versions may be accepted.
		output = "feature san=1";
		return true;
	}

	bool XboardCommand::hAccepted(const std::string& input, std::string& output)
	{
		//These commands may be sent to your engine in reply to the "feature" command; see its documentation below. 
		output = "";
		return true;
	}

	bool XboardCommand::hRejected(const std::string& input, std::string& output)
	{
		//These commands may be sent to your engine in reply to the "feature" command; see its documentation below. 
		output = "";
		return true;
	}

	bool XboardCommand::hNew(const std::string& input, std::string& output)
	{
		//Reset the board to the standard chess starting position. Set White on move. Leave force mode and set the engine to play Black. Associate the engine's clock with Black and the opponent's clock with White. Reset clocks and time controls to the start of a new game. Use wall clock for time measurement. Stop clocks. Do not ponder on this move, even if pondering is on. Remove any search depth limit previously set by the sd command. 
		engine.newboard();
		output = "";
		return true;
	}

	bool XboardCommand::hVariant(const std::string& input, std::string& output)
	{
		//variant VARNAME
		//If the game is not standard chess, but a variant, this command is sent after "new" and before the first move or "edit" command.
		output = "";
		return true;
	}

	bool XboardCommand::hQuit(const std::string& input, std::string& output)
	{
		//The chess engine should immediately exit. This command is used when xboard is itself exiting, and also between games if the -xreuse command line option is given (or -xreuse2 for the second engine). 
		output = "";
		return false; // this is only place we return false
	}

	bool XboardCommand::hRandom(const std::string& input, std::string& output)
	{
		//This command is specific to GNU Chess 4. You can either ignore it completely (that is, treat it as a no-op) or implement it as GNU Chess does. The command toggles "random" mode (that is, it sets random = !random). In random mode, the engine adds a small random value to its evaluation function to vary its play. The "new" command sets random mode off. 
		output = "";
		return true;
	}

	bool XboardCommand::hForce(const std::string& input, std::string& output)
	{
		//Set the engine to play neither color ("force mode"). Stop clocks. The engine should check that moves received in force mode are legal and made in the proper turn, but should not think, ponder, or make moves of its own.
		output = "";
		return true;
	}

	bool XboardCommand::hGo(const std::string& input, std::string& output)
	{
		//Leave force mode and set the engine to play the color that is on move. Associate the engine's clock with the color that is on move, the opponent's clock with the color that is not on move. Start the engine's clock. Start thinking and eventually make a move. 
		output = "";
		return true;
	}

	bool XboardCommand::hPlayother(const std::string& input, std::string& output)
	{
		//(This command is new in protocol version 2. It is not sent unless you enable it with the feature command.) Leave force mode and set the engine to play the color that is not on move. Associate the opponent's clock with the color that is on move, the engine's clock with the color that is not on move. Start the opponent's clock. If pondering is enabled, the engine should begin pondering. If the engine later receives a move, it should start thinking and eventually reply.
		output = "";
		return true;
	}

	bool XboardCommand::hWhite(const std::string& input, std::string& output)
	{
		//(This command is obsolete as of protocol version 2, but is still sent in some situations to accommodate older engines unless you disable it with the feature command.) Set White on move. Set the engine to play Black. Stop clocks. 
		output = "";
		return true;
	}

	bool XboardCommand::hBlack(const std::string& input, std::string& output)
	{
		//(This command is obsolete as of protocol version 2, but is still sent in some situations to accommodate older engines unless you disable it with the feature command.) Set Black on move. Set the engine to play White. Stop clocks.
		output = "";
		return true;
	}

	bool XboardCommand::hLevel(const std::string& input, std::string& output)
	{
		//level MPS BASE INC
		//Set time controls.
		output = "";
		return true;
	}

	bool XboardCommand::hSt(const std::string& input, std::string& output)
	{
		//st TIME
		//Set time controls.
		output = "";
		return true;
	}

	bool XboardCommand::hSd(const std::string& input, std::string& output)
	{
		//sd DEPTH
		//The engine should limit its thinking to DEPTH ply. The commands "level" or "st" and "sd" can be used together in an orthogonal way. If both are issued, the engine should observe both limitations: In the protocol, the "sd" command isn't a time control. It doesn't say that your engine has unlimited time but must search to exactly the given depth. It says that you should pay attention to the time control as normal, but cut off the search at the specified depth even if you have time to search deeper. If you don't have time to search to the specified depth, given your normal time management algorithm, then you will want to stop sooner than the given depth.
		//The "new" command should set the search depth back to unlimited.This is already stated in the spec.The "level" command should not affect the search depth.As it happens, xboard / WinBoard currently always sends sd(if needed) right after level, but that isn't part of the spec. 
		output = "";
		return true;
	}

	bool XboardCommand::hNps(const std::string& input, std::string& output)
	{
		//nps NODE_RATE
		//The engine should not use wall-clock time to make its timing decisions, but an own internal time measure based on the number of nodes it has searched (and will report as "thinking output"), converted to seconds through dividing by the given NODE_RATE. Example: after receiving the commands "st 8" and "nps 10000", the engine should never use more that 80,000 nodes in the search for any move. In this mode, the engine should report user CPU time used (in its thinking output), rather than wall-clock time. This even holds if NODE_RATE is given as 0, but in that case it should also use the user CPU time for its timing decisions. The effect of an "nps" command should persist until the next "new" command. 
		output = "";
		return true;
	}

	bool XboardCommand::hTime(const std::string& input, std::string& output)
	{
		//time N
		//Set a clock that always belongs to the engine. N is a number in centiseconds (units of 1/100 second). Even if the engine changes to playing the opposite color, this clock remains with the engine. 
		output = "";
		return true;
	}

	bool XboardCommand::hOtim(const std::string& input, std::string& output)
	{
		//otim N
		//Set a clock that always belongs to the opponent. N is a number in centiseconds (units of 1/100 second). Even if the opponent changes to playing the opposite color, this clock remains with the opponent.
		//If needed for purposes of board display in force mode(where the engine is not participating in the game) the time clock should be associated with the last color that the engine was set to play, the otim clock with the opposite color.
		//This business of "clocks remaining with the engine" is apparently so ambiguous that many engines implement it wrong.The clocks in fact always remain with the color.Which clock reading is relayed with "time", and which by "otim", is determined by which side the engine plays.Note that the way the clocks operateand receive extra time(in accordance with the selected time control) is not affected in any way by which moves are made by the engine, which by the opponent, and which were forced.
		//Beginning in protocol version 2, if you can't handle the time and otim commands, you can use the "feature" command to disable them; see below. The following techniques from older protocol versions also work: You can ignore the time and otim commands (that is, treat them as no-ops), or send back "Error (unknown command): time" the first time you see "time". 
		output = "";
		return true;
	}

	bool XboardCommand::hUsermove(const std::string& input, std::string& output)
	{
		//usermove MOVE
		//By default, moves are sent to the engine without a command name; the notation is just sent as a line by itself. Beginning in protocol version 2, you can use the feature command to cause the command name "usermove" to be sent before the move. Example: "usermove e2e4". 
		output = "";
		return true;
	}

	bool XboardCommand::hQuestionmark(const std::string& input, std::string& output)
	{
		//Move now. If your engine is thinking, it should move immediately; otherwise, the command should be ignored (treated as a no-op). It is permissible for your engine to always ignore the ? command. The only bad consequence is that xboard's Move Now menu command will do nothing.
		//It is also permissible for your engine to move immediately if it gets any command while thinking, as long as it processes the command right after moving, but it's preferable if you don't do this.For example, xboard may send post, nopost, easy, hard, force, quit, or other commands while the engine is on move.
		output = "";
		return true;
	}

	bool XboardCommand::hPing(const std::string& input, std::string& output)
	{
		//ping N
		//In this command, N is a decimal number. When you receive the command, reply by sending the string pong N, where N is the same number you received. Important: You must not reply to a "ping" command until you have finished executing all commands that you received before it. Pondering does not count; if you receive a ping while pondering, you should reply immediately and continue pondering. Because of the way xboard uses the ping command, if you implement the other commands in this protocol, you should never see a "ping" command when it is your move; however, if you do, you must not send the "pong" reply to xboard until after you send your move. For example, xboard may send "?" immediately followed by "ping". If you implement the "?" command, you will have moved by the time you see the subsequent ping command. Similarly, xboard may send a sequence like "force", "new", "ping". You must not send the pong response until after you have finished executing the "new" command and are ready for the new game to start.
		//The ping command is new in protocol version 2 and will not be sent unless you enable it with the "feature" command.Its purpose is to allow several race conditions that could occur in previous versions of the protocol to be fixed, so it is highly recommended that you implement it.It is especially important in simple engines that do not ponder and do not poll for input while thinking, but it is needed in all engines.
		output = "";
		return true;
	}

	bool XboardCommand::hDraw(const std::string& input, std::string& output)
	{
		//The engine's opponent offers the engine a draw. To accept the draw, send "offer draw". To decline, ignore the offer (that is, send nothing). If you're playing on ICS, it's possible for the draw offer to have been withdrawn by the time you accept it, so don't assume the game is over because you accept a draw offer. Continue playing until xboard tells you the game is over. See also "offer draw" below. 
		output = "";
		return true;
	}

	bool XboardCommand::hResult(const std::string& input, std::string& output)
	{
		//result RESULT {COMMENT}
		//After the end of each game, xboard will send you a result command. You can use this command to trigger learning. RESULT is either 1-0, 0-1, 1/2-1/2, or *, indicating whether white won, black won, the game was a draw, or the game was unfinished. The COMMENT string is purely a human-readable comment; its content is unspecified and subject to change. In ICS mode, it is passed through from ICS uninterpreted. Example:
		//result 1 - 0 {White mates}
		//Here are some notes on interpreting the "result" command.Some apply only to playing on ICS("Zippy" mode).
		//If you won but did not just play a mate, your opponent must have resigned or forfeited.If you lost but were not just mated, you probably forfeited on time, or perhaps the operator resigned manually.If there was a draw for some nonobvious reason, perhaps your opponent called your flag when he had insufficient mating material(or vice versa), or perhaps the operator agreed to a draw manually.
		//You will get a result command even if you already know the game ended-- for example, after you just checkmated your opponent.In fact, if you send the "RESULT {COMMENT}" command(discussed below), you will simply get the same thing fed back to you with "result" tacked in front.You might not always get a "result *" command, however.In particular, you won't get one in local chess engine mode when the user stops playing by selecting Reset, Edit Game, Exit or the like. 
		output = "";
		return true;
	}

	bool XboardCommand::hSetboard(const std::string& input, std::string& output)
	{
		//setboard FEN
		//The setboard command is the new way to set up positions, beginning in protocol version 2. It is not used unless it has been selected with the feature command. Here FEN is a position in Forsythe-Edwards Notation, as defined in the PGN standard. Note that this PGN standard referred to here only applies to normal Chess; Obviously in variants that cannot be described by a FEN for normal Chess, e.g. because the board is not 8x8, other pieces then PNBRQK participate, there are holdings that need to be specified, etc., xboard will use a FEN format that is standard or suitable for that varant. In particular, in FRC or CRC, WinBoard will use Shredder-FEN or X-FEN standard, i.e. it can use the rook-file indicator letter to represent a castling right (like HAha) whenever it wants, but if it uses KQkq, this will always refer to the outermost rook on the given side.
		//Illegal positions : Note that either setboard or edit can be used to send an illegal position to the engine.The user can create any position with xboard's Edit Position command (even, say, an empty board, or a board with 64 white kings and no black ones). If your engine receives a position that it considers illegal, I suggest that you send the response "tellusererror Illegal position", and then respond to any attempted move with "Illegal move" until the next new, edit, or setboard command.
		output = "";
		return true;
	}

	bool XboardCommand::hEdit(const std::string& input, std::string& output)
	{
		//The edit command is the old way to set up positions. For compatibility with old engines, it is still used by default, but new engines may prefer to use the feature command (see below) to cause xboard to use setboard instead. The edit command puts the chess engine into a special mode, where it accepts the following subcommands:
		//c	change current piece color, initially white
		//Pa4(for example)	place pawn of current color on a4
		//xa4(for example)	empty the square a4(not used by xboard)
		//#	clear board
		//.leave edit mode
		//The edit command does not change the side to move.To set up a black - on - move position, xboard uses the following command sequence :
		//	new
		//	force
		//	a2a3
		//	edit
		//	<edit commands>
		//	.
		//This sequence is used to avoid the "black" command, which is now considered obsoleteand which many engines never did implement as specified in this document.
		//After an edit command is complete, if a king and a rook are on their home squares, castling is assumed to be available to them.En passant capture is assumed to be illegal on the current move regardless of the positions of the pawns.The clock for the 50 move rule starts at zero, and for purposes of the draw by repetition rule, no prior positions are deemed to have occurred.In FRC or CRC, any rookand king put on the back rank should be considered to have castling rights, even if it later becomes apparent that they cannot be both in the initial position, because the position just set up is asymmetric.It is upto WinBoard to find work - around in cases where this is not desired, similar to the "black kludge" shown above, by setting up an earlier position, and then do a move to destroy castling rights or create e.p.rights. (Don't bet your life on it...) 
		output = "";
		return true;
	}

	bool XboardCommand::hHint(const std::string& input, std::string& output)
	{
		//If the user asks for a hint, xboard sends your engine the command "hint". Your engine should respond with "Hint: xxx", where xxx is a suggested move. If there is no move to suggest, you can ignore the hint command (that is, treat it as a no-op). 
		output = "";
		return true;
	}

	bool XboardCommand::hBk(const std::string& input, std::string& output)
	{
		//If the user selects "Book" from the xboard menu, xboard will send your engine the command "bk". You can send any text you like as the response, as long as each line begins with a blank space or tab (\t) character, and you send an empty line at the end. The text pops up in a modal information dialog. 
		output = "";
		return true;
	}

	bool XboardCommand::hUndo(const std::string& input, std::string& output)
	{
		//If the user asks to back up one move, xboard will send you the "undo" command. xboard will not send this command without putting you in "force" mode first, so you don't have to worry about what should happen if the user asks to undo a move your engine made. (GNU Chess 4 actually switches to playing the opposite color in this case.) 
		output = "";
		return true;
	}

	bool XboardCommand::hRemove(const std::string& input, std::string& output)
	{
		//If the user asks to retract a move, xboard will send you the "remove" command. It sends this command only when the user is on move. Your engine should undo the last two moves (one for each player) and continue playing the same color. 
		output = "";
		return true;
	}

	bool XboardCommand::hHard(const std::string& input, std::string& output)
	{
		//Turn on pondering (thinking on the opponent's time, also known as "permanent brain"). xboard will not make any assumption about what your default is for pondering or whether "new" affects this setting. 
		output = "";
		return true;
	}

	bool XboardCommand::hEasy(const std::string& input, std::string& output)
	{
		//Turn off pondering. 
		output = "";
		return true;
	}

	bool XboardCommand::hPost(const std::string& input, std::string& output)
	{
		//Turn on thinking/pondering output.
		output = "";
		return true;
	}

	bool XboardCommand::hNopost(const std::string& input, std::string& output)
	{
		//Turn off thinking/pondering output. 
		output = "";
		return true;
	}

	bool XboardCommand::hAnalyze(const std::string& input, std::string& output)
	{
		//Enter analyze mode.
		output = "";
		return true;
	}

	bool XboardCommand::hName(const std::string& input, std::string& output)
	{
		//name X
		//This command informs the engine of its opponent's name. When the engine is playing on a chess server, xboard obtains the opponent's name from the server. When the engine is playing locally against a human user, xboard obtains the user's login name from the local operating system. When the engine is playing locally against another engine, xboard uses either the other engine's filename or the name that the other engine supplied in the myname option to the feature command. By default, xboard uses the name command only when the engine is playing on a chess server. Beginning in protocol version 2, you can change this with the name option to the feature command
		output = "";
		return true;
	}

	bool XboardCommand::hRating(const std::string& input, std::string& output)
	{
		//In ICS mode, xboard obtains the ICS opponent's rating from the "Creating:" message that appears before each game. (This message may not appear on servers using outdated versions of the FICS code.) In Zippy mode, it sends these ratings on to the chess engine using the "rating" command. The chess engine's own rating comes first, and if either opponent is not rated, his rating is given as 0. In the future this command may also be used in other modes, if ratings are known. Example:
		//rating 2600 1500
		output = "";
		return true;
	}

	bool XboardCommand::hIcs(const std::string& input, std::string& output)
	{
		//ics HOSTNAME
		//If HOSTNAME is "-", the engine is playing against a local opponent; otherwise, the engine is playing on an Internet Chess Server (ICS) with the given hostname. This command is new in protocol version 2 and is not sent unless the engine has enabled it with the "feature" command. Example: "ics freechess.org" 
		output = "";
		return true;
	}

	bool XboardCommand::hComputer(const std::string& input, std::string& output)
	{
		//The opponent is also a computer chess engine. Some engines alter their playing style when they receive this command. 
		output = "";
		return true;
	}

	bool XboardCommand::hPause(const std::string& input, std::string& output)
	{
		//(These commands are new in protocol version 2 and will not be sent unless feature pause=1 is set. At this writing, xboard actually does not use the commands at all, but it or other interfaces may use them in the future.) The "pause" command puts the engine into a special state where it does not think, ponder, or otherwise consume significant CPU time. The current thinking or pondering (if any) is suspended and both player's clocks are stopped. The only command that the interface may send to the engine while it is in the paused state is "resume". The paused thinking or pondering (if any) resumes from exactly where it left off, and the clock of the player on move resumes running from where it stopped. 
		output = "";
		return true;
	}

	bool XboardCommand::hResume(const std::string& input, std::string& output)
	{
		//(These commands are new in protocol version 2 and will not be sent unless feature pause=1 is set. At this writing, xboard actually does not use the commands at all, but it or other interfaces may use them in the future.) The "pause" command puts the engine into a special state where it does not think, ponder, or otherwise consume significant CPU time. The current thinking or pondering (if any) is suspended and both player's clocks are stopped. The only command that the interface may send to the engine while it is in the paused state is "resume". The paused thinking or pondering (if any) resumes from exactly where it left off, and the clock of the player on move resumes running from where it stopped. 
		output = "";
		return true;
	}

	bool XboardCommand::hMemory(const std::string& input, std::string& output)
	{
		//memory N
		//This command informs the engine on how much memory it is allowed to use maximally, in MegaBytes. On receipt of this command, the engine should adapt the size of its hash tables accordingly. This command does only fix the total memory use, the engine has to decide for itself (or be configured by the user by other means) how to divide up the available memory between the various tables it wants to use (e.g. main hash, pawn hash, tablebase cache, bitbases). This command will only be sent to engines that have requested it through the memory feature, and only at the start of a game, as the first of the commands to relay engine option settings just before each "new" command. 
		output = "";
		return true;
	}

	bool XboardCommand::hCores(const std::string& input, std::string& output)
	{
		//cores N
		//This command informs the engine on how many CPU cores it is allowed to use maximally. This could be interpreted as the number of search threads for SMP engines. (Threads that do not consume significant amounts of CPU time, like I/O threads, need not be included in the count.) This command will only be sent to engines that have requested it through the smp feature. The engine should be able to respond to the "cores" command any time during a game, but it is allowed to finish a search in progress before procesing the command. (Obeying the command should take priority over finishing a ponder search, though.) In any case it will be sent at the start of every game as the last command to relay engine option settings before the "new" command. 
		output = "";
		return true;
	}

	bool XboardCommand::hEgtpath(const std::string& input, std::string& output)
	{
		//egtpath TYPE PATH
		//This command informs the engine in which directory (given by the PATH argument) it can find end-game tables of the specified TYPE. The TYPE argument can be any character string which does not contain spaces. Currently nalimov and scorpio are defined types, for Nalimov tablebases and Scorpio bitbases, respectively, but future developers of other formats are free to define their own format names. The GUI simply matches the TYPE names the engine says it supports with those that the user supplied when configuring xboard. For every match, it sends a separate "y" command. The PATH argument would normally (for Nalimov) be the pathname of the directory the EGT files are in, but could also be the name of a file, or in fact anything the particular EGT type requires. It is upto the developer of the EGT format to specify the syntax of this parameter. This command will only be sent to engines that have told the GUI they support EGTs of the given TYPE through the egt feature. It will be sent at the start of each game, before the "new" command. 
		output = "";
		return true;
	}

	bool XboardCommand::hOption(const std::string& input, std::string& output)
	{
		//option NAME[=VALUE]
		//This command changes the setting of the option NAME defined by the engine (through an earlier feature command) to the given VALUE. XBoard will in general have no idea what the option means, and will send the command only when a user changes the value of this option through a menu, or at startup of the engine (before the first 'cores' command or, if that is not sent, the first 'new' command) in reaction to command-line options. The NAME echoes back to the engine the string that was identified as an option NAME in the feature command defining the option. The VALUE is of the type (numeric or text or absent) that was implied by the option type specified in this feature command, i.e. with 'spin' and 'check' options VALUE will be a decimal integer (in the latter case 0 or 1), with 'combo' and 'string' options VALUE will be a text string, and with 'button' and 'save' options no VALUE will be sent at all. 
		output = "";
		return true;
	}

	bool XboardCommand::hMove(const std::string& input, std::string& output) {
		//See below for the syntax of moves. If the move is illegal, print an error message; see the section "Commands from the engine to xboard". If the move is legal and in turn, make it. If not in force mode, stop the opponent's clock, start the engine's clock, start thinking, and eventually make a move.
		//When xboard sends your engine a move, it normally sends coordinate algebraic notation.Examples:
		//Normal moves : e2e4
		//Pawn promotion : e7e8q
		//Castling : e1g1, e1c1, e8g8, e8c8
		//Bughouse / crazyhouse drop : P@h3
		//ICS Wild 0 / 1 castling:	d1f1, d1b1, d8f8, d8b8
		//FischerRandom castling : O - O, O - O - O(oh, not zero)
		//Note that on boards with more than 9 ranks, counting of the ranks starts at 0.
		//Beginning in protocol version 2, you can use the feature command to select SAN(standard algebraic notation) instead; for example, e4, Nf3, exd5, Bxf7 + , Qxf7#, e8 = Q, O - O, or P@h3.Note that the last form, P@h3, is a extension to the PGN standard's definition of SAN, which does not support bughouse or crazyhouse.
		//xboard doesn't reliably detect illegal moves, because it does not keep track of castling unavailability due to king or rook moves, or en passant availability. If xboard sends an illegal move, send back an error message so that xboard can retract it and inform the user". 
		engine.usermove(input, output);
		return true;
	}

	bool XboardCommand::process(const std::string& input, std::string& output) {
		for (size_t i = 0; i < mapSize; ++i) {
			if (input.rfind(m[i].name, 0) == 0) {
				return (this->*(m[i].func))(input, output);
			}
		}

		// if we are here, then the command is probably a move
		return hMove(input, output);
	}
}