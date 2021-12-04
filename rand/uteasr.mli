let swap_head list x = match list with [] -> []
										h::tl -> x::tl

let smallest_subn prev x = match prev with 
						| [] -> [[x]]
						(*| []::L -> should not happen *)
						| (h::l)::lists when x < h -> (x::l)::(smallestsubn lists x)
						| (h::l)::lists when  x > h -> (h::x::l)::(h::l)::(smallest_subn lists x)

let subseqs_aux subns l = 
    match l with 
    | [] -> subns 
    | h::tl -> subseqs_aux (smallest_subn subns h) tl
in subseqs [] l;
