@0xba088650048040ad;

struct Vector{
    x @0 :Float64;
    y @1 :Float64;
    z @2 :Float64;
}

struct PlData{
    mass @0 :Float64;
    radious @1 :Float64;
    planetId @2 :UInt32;
    v1 @3 :Float64;
    v2 @4 :Float64;
    v3 @5 :Float64;
    colourX @6 :Float64;
    colourY @7 :Float64;
    colourZ @8 :Float64;
}

struct PlPosition{
    planetId @0 :UInt32;
    positions @1 :List(Vector);
}