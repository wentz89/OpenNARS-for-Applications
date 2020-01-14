#ifndef H_NAL
#define H_NAL

///////////////////
// NAL ecosystem //
///////////////////
//Declarative reasoning abilities not covered by the sensorimotor component

//References//
//----------//
#include "Truth.h"
#include "Stamp.h"
#include "Encode.h"
#include "Memory.h"

//Methods//
//-------//
//Generates inference rule code
void NAL_GenerateRuleTable();
//Method for the derivation of new events as called by the generated rule table
void NAL_DerivedEvent(Term conclusionTerm, long conclusionOccurrence, Truth conclusionTruth, Stamp stamp, long currentTime, double parentPriority);
//macro for syntactic representation, increases readability, double premise inference
#define R2(premise1, premise2, _, conclusion, truthFunction) NAL_GenerateRule(#premise1, #premise2, #conclusion, #truthFunction, true);
//macro for syntactic representation, increases readability, single premise inference
#define R1(premise1, _, conclusion, truthFunction) NAL_GenerateRule(#premise1, NULL, #conclusion, #truthFunction, false);
//macro for term reductions
#define Reduce(pattern, replacement) NAL_GenerateReduction("(" #pattern " --> M) ", "(" #replacement " --> M)"); NAL_GenerateReduction("(M --> " #pattern ")", "(M --> " #replacement ")");

#endif

//Inference rules//
//---------------//
#ifdef H_NAL_RULES

//NAL1 rules
R1( (S --> P), |-, (P --> S), Truth_Conversion )
R2( (S --> M), (M --> P), |-, (S --> P), Truth_Deduction )
R2( (A --> B), (A --> C), |-, (C --> B), Truth_Abduction )
R2( (A --> C), (B --> C), |-, (B --> A), Truth_Induction )
R2( (A --> B), (B --> C), |-, (C --> A), Truth_Exemplification )
//NAL2 rules
R2( (S --> P), (P --> S), |-, (S <-> P), Truth_Intersection )
R2( (P --> M), (S --> M), |-, (S <-> P), Truth_Comparison )
R2( (M --> P), (M --> S), |-, (S <-> P), Truth_Comparison )
R2( (M --> P), (S <-> M), |-, (S --> P), Truth_Analogy )
R2( (P --> M), (S <-> M), |-, (P --> S), Truth_Analogy )
R2( (M <-> P), (S <-> M), |-, (S <-> P), Truth_Resemblance )
R1( ({A} <-> {B}), |-, (A <-> B), Truth_Identity )
R1( ([A] <-> [B]), |-, (A <-> B), Truth_Identity )
R1( (S --> {P}), |-, (S <-> {P}), Truth_Identity )
R1( ([S] --> P), |-, ([S] <-> {P}), Truth_Identity )
R1( (S <-> {P}), |-, (S --> {P}), Truth_Identity )
R1( ([S] <-> P), |-, ([S] --> P), Truth_Identity )
R1( ({S} <-> {P}), |-, ({P} --> {S}), Truth_Identity )
R1( ([S] <-> [P]), |-, ([P] --> [S]), Truth_Identity )
R1( (S <-> P), |-, (S --> P), Truth_StructuralDeduction )
R1( (S --> P), |-, (S <-> P), Truth_StructuralAbduction )
//NAL3 rules
R2( (P --> M), (S --> M), |-, ((S | P) --> M), Truth_Intersection )
R2( (P --> M), (S --> M), |-, ((S & P) --> M), Truth_Union )
R2( (P --> M), (S --> M), |-, ((S ~ P) --> M), Truth_Difference )
R2( (M --> P), (M --> S), |-, (M --> (P & S)), Truth_Intersection )
R2( (M --> P), (M --> S), |-, (M --> (P | S)), Truth_Union )
R2( (M --> P), (M --> S), |-, (M --> (P - S)), Truth_Difference )
//NAL4 rules
R1( ((A * B) --> R), |-, (A --> (R / B)), Truth_Identity )
R1( ((A * B) --> R), |-, (B --> (R % A)), Truth_Identity )
R1( (R --> (A * B)), |-, ((R \\ B) --> A), Truth_Identity )
R1( (R --> (A * B)), |-, ((R % A) --> B), Truth_Identity )
R1( (A --> (R / B)), |-, ((A * B) --> R), Truth_Identity )
R1( (B --> (R % A)), |-, ((A * B) --> R), Truth_Identity )
R1( ((R \\ B) --> A), |-, ((A * B) --> R), Truth_Identity )
R1( ((R % A) --> B), |-, (R --> (A * B)), Truth_Identity )

#endif

#ifdef H_NAL_REDUCTIONS

//Extensional intersection and union
Reduce( (A & A), A )
Reduce( (A | A), A )
//Extensional set
Reduce( ({A} & {B}),     {A B}             )
Reduce( ({A X} & {B}),   {A (B . X)}       )
Reduce( ({A X} & {B Y}), {A (B . (X . Y))} )
Reduce( {A A},           {A}               )
//Intensional set
Reduce( ([A] & [B]),     [A B]             )
Reduce( ([A X] & [B]),   [A (B . X)]       )
Reduce( ([A X] & [B Y]), [A (B . (X . Y))] )
Reduce( [A A],           [A]               )

#endif