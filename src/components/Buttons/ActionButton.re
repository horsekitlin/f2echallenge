[@react.component]
let make = (~status, ~handleTooglePlay) =>
  switch (status) {
  | "play" => <button className="fa fa-pause" onClick={handleTooglePlay("pause")} />
  | "pause" => <button className="fa fa-play" onClick={handleTooglePlay("play")} />
  | _ => <button className="fa fa-refresh" onClick={handleTooglePlay("refresh")} />
  };