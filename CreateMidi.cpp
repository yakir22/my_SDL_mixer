#include "midifile/MidiFile.h"
#include "midifile/Options.h"
#include <random>
#include <map>
#include <list>
using namespace std;
using namespace smf;
// TODO :: add (yakir)
extern "C" int CreateMidi(const char *filename)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> starttime(0, 100);
	uniform_int_distribution<int> duration(1, 8);
	uniform_int_distribution<int> pitch(36, 84);
	uniform_int_distribution<int> velocity(40, 100);

	MidiFile midifile;
	int track = 0;
	int channel = 0;
	int instr = 0;
	midifile.addTimbre(track, 0, channel, instr);

	std::map<std::string, int> keyToNote = { 
		{"A0" , 21},
		{"A1" , 33},
		{"A2" , 45},
		{"A3" , 57},
		{"A4" , 69},
		{"A5" , 81},
		{"A6" , 93},
		{"A7" , 105},
		{"Ab1" , 32},
		{"Ab2" , 44},
		{"Ab3" , 56},
		{"Ab4" , 68},
		{"Ab5" , 80},
		{"Ab6" , 92},
		{"Ab7" , 104},
		{"B0" , 23},
		{"B1" , 35},
		{"B2" , 47},
		{"B3" , 59},
		{"B4" , 71},
		{"B5" , 83},
		{"B6" , 95},
		{"B7" , 107},
		{"Bb0" , 22},
		{"Bb1" , 34},
		{"Bb2" , 46},
		{"Bb3" , 58},
		{"Bb4" , 70},
		{"Bb5" , 82},
		{"Bb6" , 94},
		{"Bb7" , 106},
		{"C1" , 24},
		{"C2" , 36},
		{"C3" , 48},
		{"C4" , 60},
		{"C5" , 72},
		{"C6" , 84},
		{"C7" , 96},
		{"C8" , 108},
		{"D1" , 26},
		{"D2" , 38},
		{"D3" , 50},
		{"D4" , 62},
		{"D5" , 74},
		{"D6" , 86},
		{"D7" , 98},
		{"Db1" , 25},
		{"Db2" , 37},
		{"Db3" , 49},
		{"Db4" , 61},
		{"Db5" , 73},
		{"Db6" , 85},
		{"Db7" , 97},
		{"E1" , 28},
		{"E2" , 40},
		{"E3" , 52},
		{"E4" , 64},
		{"E5" , 76},
		{"E6" , 88},
		{"E7" , 100},
		{"Eb1" , 27},
		{"Eb2" , 39},
		{"Eb3" , 51},
		{"Eb4" , 63},
		{"Eb5" , 75},
		{"Eb6" , 87},
		{"Eb7" , 99},
		{"F1" , 29},
		{"F2" , 41},
		{"F3" , 53},
		{"F4" , 65},
		{"F5" , 77},
		{"F6" , 89},
		{"F7" , 101},
		{"G1" , 31},
		{"G2" , 43},
		{"G3" , 55},
		{"G4" , 67},
		{"G5" , 79},
		{"G6" , 91},
		{"G7" , 103},
		{"Gb1" , 30},
		{"Gb2" , 42},
		{"Gb3" , 54},
		{"Gb4" , 66},
		{"Gb5" , 78},
		{"Gb6" , 90},
		{"Gb7" , 102} 
	};

	char song[1024];
	const char* song1 = "G3,E3,E3, ,F3,D3,D3, ,C3,D3,E3,F3,G3,G3,G3, ,G3,E3,E3, ,F3,D3,D3, ,C3,E3,G3,G3,C3, , , ,D3,D3,D3,D3,D3,E3,F3" 
		", ,E3,E3,E3,E3,E3,F3,G3, ,G3,E3,E3, ,F3,D3,D3, ,C3,E3,G3,G3,C3";
	
	strcpy(song,song1);
	std::list<int> notes;
	auto tok = strtok(song,",");
	while (tok)
	{
		notes.push_back(keyToNote[tok]);
		tok = strtok(nullptr, ",");
	}

	int tpq = midifile.getTPQ();
	int count = 10;
	//auto noteTimeInMillis = 250;

	int i = 0;
	for (auto it : notes)
	{
		int starttick = int(( 2 + i/2.0) * tpq);
		int key = it;
		int endtick = int (starttick + (1/4.0)*tpq);
		if ( key != 0)
		{
			midifile.addNoteOn(track, starttick, channel, key, velocity(mt));
			midifile.addNoteOff(track, endtick, channel, key);
		}
		i++;
	}
	midifile.sortTracks();  
	midifile.write(filename);
	return 0;
}
