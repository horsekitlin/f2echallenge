[@bs.val] external require: string => unit = "";

let rec getElementAt = (~index: int, l: list('a)) =>
  switch l {
  | [] => None
  | [head, ..._] when index <= 0 => Some(head)
  | [head, ...tail] => getElementAt(~index=index-1, tail)
  };

let rec removeByIndex = (~targetIndex: int, index: int, theList: list('a)) => {
  let [head, ...tail] = theList;

  switch theList {
  | [] => []
  | l when index === targetIndex => tail
  | _ => [head, ...removeByIndex(targetIndex, index + 1, tail)]
  };
};

let removeInListByIndex = (~targetIndex: int, theList: list('a)) => {
  switch (List.length(theList)) {
  | 0 => []
  | 1 => []
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