[@bs.val] external require: string => unit = "";

let rec removeByIndex = (~targetIndex: int, index: int, theList: list('a)) => {
  let [head, ...tail] = theList;

  switch theList {
  | [] => []
  | l when index === targetIndex => tail
  | _ => [head, ...removeByIndex(targetIndex, index + 1, tail)]
  };
};

let removeInListByIndex = (~targetIndex: int, theList: list('a)) => {
  switch theList {
  | [] => []
  | _ => removeByIndex(targetIndex, 0, theList)
  };
};

/**
 * Remove the first `~index` elements of `theList`.
 */
let rec drop = (~index: int, theList: list('a)) => {
  switch theList {
    | [] => []
    | l when index <= 0 => l
    | [_, ...tail] => drop(~index=index-1, tail)
    };
};

/**
 * Create a copy of `theList` whose element at index `~index`
 * is `~value`.
 */
let setElementAt = (~index: int, ~value: 'a, theList: list('a)) => {
  ListLabels.mapi(
    ~f=(i,x) => (i==index)? value: x,
    theList
  );
};